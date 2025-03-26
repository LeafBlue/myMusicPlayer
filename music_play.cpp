#include "music_play.h"

music_play::music_play(QObject *parent)
    : QObject{parent}
{
    cur_song = nullptr;
    audiooutput = new QAudioOutput();

    player.setAudioOutput(audiooutput);
    setvoice(50);

    music_progeress = new QTimer(this);
    connect(music_progeress,&QTimer::timeout,this,&music_play::get_nowposition);
}

void music_play::setsource_(song_info& song)
{

    //在这里进行一次拷贝
    if(cur_song!=nullptr){
        delete cur_song;
        cur_song = nullptr;
    }
    cur_song = new song_info(song);

    player.setSource(QUrl::fromLocalFile(cur_song->getsong_filename()));



}

void music_play::play_()
{
    if(player.mediaStatus() == QMediaPlayer::LoadingMedia){
        connect(&player,&QMediaPlayer::mediaStatusChanged,[&,this](QMediaPlayer::MediaStatus status){
            if(status == QMediaPlayer::LoadedMedia){

                //获取一个图片
                const QMediaMetaData metadata = player.metaData();
                this->cur_music_img = metadata.value(QMediaMetaData::ThumbnailImage).value<QImage>();

                player.play();
                disconnect(&player,&QMediaPlayer::mediaStatusChanged,nullptr,nullptr);


            }
        });
    }else{
        player.play();
    }
    if (!music_progeress->isActive()) {   // 确保定时器未启动
        music_progeress->start(200);      // 启动定时器
    }
}

void music_play::pause_()
{
    player.pause();
    music_progeress->stop();
}

//应该在创建时获取一次音量
void music_play::setvoice(int voice_num)
{
    qreal v = static_cast<qreal>(voice_num);
    audiooutput->setVolume(v/100);
}

void music_play::get_nowposition()
{
    int pos_1 = player.position();
    int pos_2 = player.duration();
    emit send_position(pos_1);

    if (pos_2 > 0 && pos_1 >= pos_2 - 200) { // 检测是否接近结束
        emit send_stop();
    }
}

void music_play::set_nowposition(int pos_)
{
    player.setPosition(pos_);
}



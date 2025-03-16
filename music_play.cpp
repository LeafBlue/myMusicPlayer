#include "music_play.h"

music_play::music_play(QObject *parent)
    : QObject{parent}
{
    cur_song = nullptr;
    audiooutput = new QAudioOutput();
    setvoice(100);
}

void music_play::setsource_(song_info song)
{

    //在这里进行一次拷贝
    cur_song = &song;//指向的应该是map中的地址

    player.setSource(cur_song->getsong_filename());
}

void music_play::play_()
{
    player.play();
}

void music_play::pause_()
{
    player.pause();
}

//应该在创建时获取一次音量
void music_play::setvoice(int voice_num)
{
    player.setAudioOutput(audiooutput);
    qreal v = static_cast<qreal>(voice_num);
    audiooutput->setVolume(v/100);
}



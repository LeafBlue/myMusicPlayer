#ifndef MUSIC_PLAY_H
#define MUSIC_PLAY_H

#include <QObject>
#include "song_info.h"
#include<QMediaPlayer>
#include<QMediaMetaData>
#include<QImage>
#include<QTimer>
#include<QAudioOutput>


class music_play : public QObject
{
    Q_OBJECT
private:




    QTimer *music_progeress;



public:

    song_info *cur_song;
    QMediaPlayer player;
    QAudioOutput *audiooutput;

    //存个当前音乐的图片
    QImage cur_music_img;


    explicit music_play(QObject *parent = nullptr);

    void setsource_(song_info& song);

    void play_();

    void pause_();

    void setvoice(int voice_num);

    void get_nowposition();

    void set_nowposition(int pos_);


signals:
    void send_position(int pos_);

    void send_stop();
};

#endif // MUSIC_PLAY_H

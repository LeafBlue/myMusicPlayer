#ifndef MUSIC_PLAY_H
#define MUSIC_PLAY_H

#include <QObject>
#include "song_info.h"
#include<QMediaPlayer>
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


    explicit music_play(QObject *parent = nullptr);

    void setsource_(song_info song);

    void play_();

    void pause_();

    void setvoice(int voice_num);


signals:
};

#endif // MUSIC_PLAY_H

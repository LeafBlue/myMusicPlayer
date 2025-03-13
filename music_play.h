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
    song_info *cur_song;
    QMediaPlayer player;
    QAudioOutput *audiooutput;

    QTimer *music_progeress;



public:
    explicit music_play(QObject *parent = nullptr);

    void setsource(const song_info& song);

    void play_();

    void pause_();

    void setvoice();


signals:
};

#endif // MUSIC_PLAY_H

#include "song_list.h"

song_list::song_list(QObject *parent)
    : QObject{parent}
{}

QVector<int> &song_list::getlist_song()
{
    return this->list_song;
}

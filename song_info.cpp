#include "song_info.h"

song_info::song_info(QObject *parent)
    : QObject{parent}
{}

void song_info::setSong(QString song_name,QString singer,QString song_filename,int song_time,QString song_pic){

    //设置id
    this->song_name = song_name;
    this->singer = singer;
    this->song_filename = song_filename;
    this->song_time = song_time;
    this->song_pic = song_pic;

}

void song_info::setSong(int song_id, QString song_name, QString singer, QString song_filename, int song_time, QString song_pic)
{
    this->song_id = song_id;
    this->song_name = song_name;
    this->singer = singer;
    this->song_filename = song_filename;
    this->song_time = song_time;
    this->song_pic = song_pic;
}
int song_info::getsongid()const{
    return this->song_id;
}
QString song_info::getsongname()const{
    return this->song_name;
}
QString song_info::getsinger()const{
    return this->singer;
}
QString song_info::getsong_filename()const{
    return this->song_filename;
}
QString song_info::getsong_pic()const{
    return this->song_pic;
}
int song_info::getsong_time()const{
    return this->song_time;
}
int song_info::getlast_time()const{
    return this->last_time;
}

void song_info::setlast_time(int lasttime){
    this->last_time = lasttime;
}

#include "song_list.h"

song_list::song_list()
{}



int song_list::getlistnum() const{
    return this->list_num;
}
QString song_list::getlistname() const{
    return this->list_name;
}
QString song_list::getlistpic() const{
    return this->list_pic;
}
QString song_list::getlistinfo() const{
    return this->list_info;
}

void song_list::setlist(int list_num,const QString& list_name,const QString& list_pic,const QString& list_info){
    this->list_num = list_num;
    this->list_name = list_name;
    this->list_pic = list_pic;
    this->list_info = list_info;
}

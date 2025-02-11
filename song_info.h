#ifndef SONG_INFO_H
#define SONG_INFO_H

#include <QObject>

class song_info : public QObject
{
    Q_OBJECT
private:
    //音乐编号
    int song_id;
    //歌名
    QString song_name;
    //歌手
    QString singer;
    //歌曲路径
    QString song_filename;
    //歌曲图片
    QString song_pic;
    //歌曲时长（秒）如果需要显示再专门用一个函数转化为分+秒
    int song_time;
    //上次暂停时间（秒）
    int last_time;



public:
    explicit song_info(QObject *parent = nullptr);

    void setSong(QString song_name,QString singer,QString song_filename,int song_time,QString song_pic = "");
    int getsongid();
    QString getsongname();
    QString getsinger();
    QString getsong_filename();
    QString getsong_pic();
    int getsong_time();
    int getlast_time();

    void setlast_time(int lasttime);





signals:



};

#endif // SONG_INFO_H

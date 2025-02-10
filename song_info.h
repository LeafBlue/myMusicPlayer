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

signals:



};

#endif // SONG_INFO_H

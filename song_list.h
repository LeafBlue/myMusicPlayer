#ifndef SONG_LIST_H
#define SONG_LIST_H

#include <QObject>

class song_list : public QObject
{
    Q_OBJECT
private:
    //歌单文件存储在项目路径下指定文件夹内，可能需要维护一个歌单统计文件

    //歌单编号//默认0为全部音乐，1为本地音乐，2为我的收藏，后面是歌单
    int list_num;
    //歌单名字
    QString list_name;

public:
    explicit song_list(QObject *parent = nullptr);

signals:
};

#endif // SONG_LIST_H

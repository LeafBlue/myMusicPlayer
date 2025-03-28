#ifndef SONG_LIST_H
#define SONG_LIST_H

#include<QVector>
#include<QString>
#include"song_info.h"
/*
在项目目录下创建一个文件夹 ，就叫songlist
内部存储csv文件
song.csv，用来存储所有歌的信息
songlist.csv，用来存储所有歌单信息
1.csv，作为歌单编号.csv，里面存储所有的歌的id，动态加载
1.csv 所有音乐 2.我的收藏

在程序启动时，将所有歌曲信息和歌单信息读取到系统中，用vector 存储，不读取歌单对应信息
然后 加载当前音乐和当前歌单（需要一个东西存储上次播放歌单，上次播放音乐）

创建一个csv文件，记录上次播放歌单编号和歌曲编号，根据存储的信息加载

可以添加歌曲到歌单，添加时，加载一遍要添加的歌单，检测是否重复，并且重新保存
从歌单中删除歌曲，删除时，要同时删除当前歌单vector以及更新文件中内容

可以添加歌单，需要创建文件，并用当前新添加的歌单取代




*/

class song_list
{

private:
    //歌单文件存储在项目路径下指定文件夹内，可能需要维护一个歌单统计文件

    //歌单编号//默认0 我的收藏，1 本地音乐，2 最近播放，3 全部音乐
    int list_num;
    //歌单名字
    QString list_name;
    //歌单图标
    QString list_pic;
    //歌单介绍
    QString list_info;

    QVector<int> v;

public:
    explicit song_list();


    int getlistnum() const;
    QString getlistname() const;
    QString getlistpic() const;
    QString getlistinfo() const;

    void setlist(int list_num,const QString& list_name,const QString& list_pic,const QString& list_info);

    void setlist_1(int list_num,const QVector<int>& v);

    QVector<int>& getlist_1();

    void setlistname(QString name);

};

#endif // SONG_LIST_H

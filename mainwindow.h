#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QStyle>
#include<QWidget>
#include<QObject>
#include<QLayout>
#include<QPushButton>
#include<QLabel>
#include<QFont>
#include<QScrollArea>
#include<QSlider>

#include<QPixmap>
#include<QTime>
#include<QStringList>
#include<QTableWidget>
#include<QList>
#include<QBitmap>
#include<QPainter>
#include<QLayoutItem>

#include<QMediaPlayer>
#include<QMediaFormat>
#include<QFileInfo>
#include<QMediaMetaData>
#include<QDebug>
#include<QFileDialog>
#include<QAudioOutput>
#include<algorithm>

#include"song_tool.h"
#include"songlistlabel.h"
#include"wid_songlist.h"
#include"wid_ctrl.h"
#include"music_play.h"
#include<QHash>
#include<QProgressDialog>
#include<QFuture>
#include<QFutureWatcher>
#include<QtConcurrent/QtConcurrentRun>
#include<QMessageBox>

#include<cstdlib>
#include<ctime>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:



    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setwindow();
    void settitlecolumn();
    void setworkarea();
    void setcontrol();

    void setright1(int songlist_id = 3);
    void setlist1(song_list* songlist = nullptr,int page = 1);


    void settitle(QString window_title);
    void set_songinfo();
    void set_songlist_info(int songlist_id);
    void set_songlist_menu(QVBoxLayout *in_scroolwid,QWidget *in_scroll);

    QString to_time(int second_time);
    int of_time(QString minute_time);

    //设置一个音量进度条，默认隐藏
    void set_voice_slider();

    //进入程序加载
    void get_map_data();
    //创建文件
    void create_files();

    //添加音乐（从本地）
    void addmusicfromfile(int list_id);

    //播放！
    void play_music(int cur_songid = -1,int playmusic_id = -1);
    void pause_music();

    void prev_();
    void next_();

private:
    //界面相关
    QWidget *center;
    QWidget *title;
    QHBoxLayout *work_area;
    QHBoxLayout *control_area;
    QLabel *title_text;
    QLabel *music_name;
    QLabel *music_pic;
    QLabel *nowtime;
    QLabel *endtime;
    QLabel *list_pic;
    QLabel *list_name;
    QScrollArea *scroll;
    QVBoxLayout *right;
    QSlider *slider;



    //当前音乐
    //song_info* cur_song;
    //当前打开歌单
    song_list* cur_list;
    //QVector<int> cur_list;
    //当前 播放列表
    song_list* play_list;

    //文件工具
    file_tool *filetool;

    //控制工具
    wid_ctrl *ctrl_wid_;
    //播放工具
    music_play *player_;


    //全局变量，存储所有歌曲信息
    QMap<int,song_info> map;

    //额外维护一个查询功能
    QHash<QString,int> check_hash;


    //存储文件中读到的数据
    //歌单列表
    QVector<song_list> songlist_v;

    QMediaPlayer add_player;


    //整个全局使用的音量进度条
    QWidget *wid_vs;
    QSlider *voice_slider;






};
#endif // MAINWINDOW_H

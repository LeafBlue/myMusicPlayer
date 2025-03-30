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
#include"menu_of_song.h"
#include"dialog_label.h"
#include"toast.h"
#include"list_upmenu.h"
#include"titlebar.h"

#include<QHash>
#include<QProgressDialog>
#include<QFuture>
#include<QFutureWatcher>
#include<QtConcurrent/QtConcurrentRun>
#include<QMessageBox>
#include<QCursor>
#include<QMenu>
#include<QAction>

#include<cstdlib>
#include<ctime>

#include<QLineEdit>
#include<QCheckBox>


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
    void setlistbtn(int songlist_id);

    void setlist1(song_list* songlist = nullptr,int page = 1);


    void settitle(QString window_title);
    void set_songinfo();
    void set_songlist_info(int songlist_id);
    void set_songlist_menu();

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

    //添加歌单
    void add_list(QString& list_name);

    //歌单右键菜单设置
    void list_rightevent(songlistlabel *label);
    void changelistname(songlistlabel *label);
    void deletelist(songlistlabel *label);

    //歌曲菜单操作
    void deletesongfromlist(int songinfoid = -1);
    void addsongtolist_dialog(int songinfoid = -1);

    void addsongtolist(int songlist_id,int songinfoid = -1);
    //为最近播放单独写添加函数
    void add_to_recentplay(int songinfoid);

private:
    //界面相关
    QWidget *center;
    TitleBar *title;
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

    QVBoxLayout *in_scroolwid;
    QVector<songlistlabel*> song_list_labels;

    QWidget *r_list_btn;
    QHBoxLayout *list_btn_layout;

    //进度条调整标志
    bool user_set_slider;

    //当前音乐
    //song_info* cur_song;
    //当前打开歌单
    song_list* cur_list;
    //QVector<int> cur_list;
    //当前 播放列表
    song_list* play_list;
    //维护一个数据存储当前“页码”
    int cur_page;

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


    //存储一下“我的收藏”列表
    QSet<int> my_favorite;
    //存储一下最近播放列表
    QVector<int> recent_play;

    //这个用来存储复选框
    QSet<int> check_data;
    bool opencheck;



};
#endif // MAINWINDOW_H

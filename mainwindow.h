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

#include"song_tool.h"
#include"songlistlabel.h"

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

    void setright1(QVBoxLayout *right,int songlist_id = 3);
    void setlist1(QVBoxLayout *right,song_list* songlist = nullptr);


    void settitle(QString window_title);
    void set_songinfo();
    void set_songlist_info();
    void set_songlist_menu(QVBoxLayout *in_scroolwid,QWidget *in_scroll);

    QString to_time(int second_time);
    int of_time(QString minute_time);

    //进入程序加载
    void get_map_data();
    //创建文件
    void create_files();

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

    //当前音乐
    song_info* cur_song;

    //文件工具
    file_tool *filetool;

    //全局变量，存储所有歌曲信息
    QMap<int,song_info> map;
    //存储文件中读到的数据
    //歌单列表
    QVector<song_list> songlist_v;



};
#endif // MAINWINDOW_H

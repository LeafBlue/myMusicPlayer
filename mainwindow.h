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
#include"song_tool.h"
#include<QPixmap>
#include<QTime>
#include<QStringList>
#include<QTableWidget>
#include<QList>
#include<QBitmap>
#include<QPainter>

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

    void setright1(QVBoxLayout *right);
    void setlist1(QVBoxLayout *right,song_list* songlist = nullptr);


    void setright2(QVBoxLayout *right);


    void settitle(QString window_title);
    void set_songinfo();
    void set_songlist_info();
    void set_songlist_menu(QVBoxLayout *in_scroolwid);

    QString to_time(int second_time);
    int of_time(QString minute_time);


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

    file_tool *filetool;

    //存储文件中读到的数据
    QVector<song_list> songlist_v;

};
#endif // MAINWINDOW_H

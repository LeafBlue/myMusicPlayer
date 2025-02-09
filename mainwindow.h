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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:



    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setwindow();
    void settitlecolumn();
    void settitle(QString window_title);
    void setworkarea();
    void setcontrol();

private:
    //界面相关
    QWidget *center;
    QWidget *title;
    QHBoxLayout *work_area;
    QHBoxLayout *control_area;
    QLabel *title_text;
};
#endif // MAINWINDOW_H

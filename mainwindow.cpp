#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //关闭界面后立刻释放内存
    setAttribute(Qt::WA_DeleteOnClose);
    //界面初始化
    center = nullptr;
    title = nullptr;
    work_area = nullptr;
    title_text = nullptr;


    setwindow();
    settitlecolumn();
    settitle(QObject::tr("我的音乐播放器"));
    setworkarea();

}

MainWindow::~MainWindow() {}

void MainWindow::setwindow()
{
    resize(1080,720);
    setWindowFlags(Qt::FramelessWindowHint);

    center = new QWidget(this);
    center->setStyleSheet("background-color: silver;");

    setCentralWidget(center);
    center->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout(center);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    title = new QWidget(center);
    title->setFixedHeight(50);
    title->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    title->setStyleSheet("background-color: lightgray;");

    work_area = new QHBoxLayout();
    work_area->setContentsMargins(0,0,0,0);
    work_area->setSpacing(0);


    layout->addWidget(title,0);
    layout->addLayout(work_area,4);
}

void MainWindow::settitlecolumn()
{
    QHBoxLayout *title_inwid = new QHBoxLayout(title);
    title_inwid->setContentsMargins(0,0,0,0);
    title_inwid->setSpacing(0);

    title_text = new QLabel(title);
    title_text->setStyleSheet("border:none;font-size:25px;");
    title_inwid->addWidget(title_text);

    //弹性空间
    title_inwid->addStretch();

    QPushButton *closewindow = new QPushButton(title);
    closewindow->setText(QObject::tr("×"));
    closewindow->setStyleSheet("QPushButton { background-color: black;color:silver;font-size:35px;font-weight: bold; }"
                               "QPushButton:hover { background-color: black;color:red;font-size:35px;font-weight: bold; }");
    closewindow->setFixedSize(50,50);

    connect(closewindow,&QPushButton::clicked,this,&MainWindow::close);
    title_inwid->addWidget(closewindow);
}



void MainWindow::settitle(QString window_title)
{
    title_text->setText(window_title);
}

void MainWindow::setworkarea()
{
    QWidget *word_wid = new QWidget(center);//套一个大的widget，这很重要！！！
    word_wid->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    work_area->addWidget(word_wid);

    QHBoxLayout *in_wid = new QHBoxLayout(word_wid);

    QVBoxLayout *left = new QVBoxLayout();
    left->setContentsMargins(0,0,0,0);
    left->setSpacing(0);
    in_wid->addLayout(left,2);

    QVBoxLayout *right = new QVBoxLayout();
    right->setContentsMargins(0,0,0,0);
    right->setSpacing(0);
    in_wid->addLayout(right,5);

    //定义一个滚动条组件
    QScrollArea *scroll = new QScrollArea(center);
    scroll->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    scroll->setWidgetResizable(true);
    left->addWidget(scroll);

    //定义一个widget
    QWidget *in_scroll = new QWidget(scroll);
    in_scroll->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    scroll->setWidget(in_scroll);

    //在这里面再放一个布局
    QVBoxLayout *in_scroolwid = new QVBoxLayout(in_scroll);

    for (int i = 0; i < 8; ++i) {
        QLabel *left_label = new QLabel(in_scroll);
        left_label->setText("菜单示例");
        left_label->setStyleSheet("border:2px solid black;font-size:20px;");
        left_label->setAlignment(Qt::AlignCenter);  // 居中对齐文本
        left_label->setFixedHeight(50);
        left_label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

        in_scroolwid->addWidget(left_label);
    }
    in_scroolwid->addStretch();
}












#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //关闭界面后立刻释放内存
    //setAttribute(Qt::WA_DeleteOnClose);
    //界面初始化
    center = nullptr;
    title = nullptr;
    work_area = nullptr;
    title_text = nullptr;
    control_area=nullptr;


    setwindow();
    settitlecolumn();
    settitle(QObject::tr("  我的音乐播放器"));
    setworkarea();
    setcontrol();

}

MainWindow::~MainWindow() {}
//--------------------------------------------------------------------绘制界面 开始--------------------------------------------------------------------
void MainWindow::setwindow()
{
    resize(1080,720);
    setWindowFlags(Qt::FramelessWindowHint);

    center = new QWidget(this);
    center->setStyleSheet("background-color: white;");

    setCentralWidget(center);
    center->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout(center);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    title = new QWidget(center);
    title->setFixedHeight(50);
    title->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    title->setStyleSheet("background-color: DimGray;");

    work_area = new QHBoxLayout();
    work_area->setContentsMargins(0,0,0,0);
    work_area->setSpacing(0);

    control_area = new QHBoxLayout();
    control_area->setContentsMargins(0,0,0,0);
    control_area->setSpacing(0);

    layout->addWidget(title,1);
    layout->addLayout(work_area,8);
    layout->addLayout(control_area,1);
}

void MainWindow::settitlecolumn()
{
    QHBoxLayout *title_inwid = new QHBoxLayout(title);
    title_inwid->setContentsMargins(0,0,0,0);
    title_inwid->setSpacing(0);

    title_text = new QLabel(title);
    title_text->setStyleSheet("border:none;font-size:20px;color:white;");
    title_inwid->addWidget(title_text);

    //弹性空间
    title_inwid->addStretch();

    QPushButton *closewindow = new QPushButton(title);
    closewindow->setText(QObject::tr("×"));
    closewindow->setStyleSheet("QPushButton { background-color: LightSlateGray;color:silver;font-size:35px;font-weight: bold;border:0.5px solid DimGray; }"
                               "QPushButton:hover { background-color: DarkSlateGray;color:silver;font-size:35px;font-weight: bold;border:1px solid DimGray; }");
    closewindow->setFixedSize(50,50);

    connect(closewindow,&QPushButton::clicked,this,&MainWindow::close);
    title_inwid->addWidget(closewindow);
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
    in_wid->addLayout(left,1);

    QVBoxLayout *right = new QVBoxLayout();
    right->setContentsMargins(0,0,0,0);
    right->setSpacing(0);
    in_wid->addLayout(right,4);

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
    in_scroolwid->setSpacing(0);
    for (int i = 0; i < 6; ++i) {

        QLabel *left_label = new QLabel(in_scroll);
        if(i == 0){
            left_label->setText("我的音乐");
            left_label->setStyleSheet("border:1px solid lightgray;font-size:16px;color:gray;");
            left_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            left_label->setFixedHeight(50);
            left_label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
        }
        else if(i == 5){
            left_label->setText("创建的歌单");
            left_label->setStyleSheet("border:1px solid lightgray;font-size:16px;color:gray;");
            left_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            left_label->setFixedHeight(50);
            left_label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
        }
        else{
            if(i == 1){
                left_label->setText("  我的收藏");
            }else if(i == 2){
                left_label->setText("  本地音乐");
            }else if(i == 3){
                left_label->setText("  最近播放");
            }else if(i == 4){
                left_label->setText("  全部音乐");
            }
            left_label->setStyleSheet("border:1px solid lightgray;font-size:18px;color:black;font-weight: bold;");
            left_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            left_label->setFixedHeight(50);
            left_label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
        }
        in_scroolwid->addWidget(left_label);
    }
    /*
    for (int i = 0; i < 20; ++i) {
        QLabel *left_label = new QLabel(in_scroll);
        left_label->setText("  歌单示例");
        left_label->setStyleSheet("border:1px solid lightgray;font-size:18px;color:black;font-weight: bold;");
        left_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        left_label->setFixedHeight(50);
        left_label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

        in_scroolwid->addWidget(left_label);
    }*/
    //为了避免label不够时呈现出均匀分布，设置一个占位将它们挤在上面
    in_scroolwid->addStretch();
}

void MainWindow::setcontrol()
{
    QWidget *ctrl_wid = new QWidget(center);
    ctrl_wid->setFixedHeight(50);
    ctrl_wid->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    control_area->addWidget(ctrl_wid);
    ctrl_wid->setStyleSheet("background-color: DimGray;");

    QHBoxLayout *ctrl_biglayout = new QHBoxLayout(ctrl_wid);
    ctrl_biglayout->setContentsMargins(5,0,0,0);
    ctrl_biglayout->setSpacing(0);

    QWidget *music_info = new QWidget(ctrl_wid);
    music_info->setFixedSize(200,50);
    music_info->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);


    QLabel *music_name = new QLabel(music_info);
    music_name->setFixedSize(200,50);
    music_name->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    music_name->setStyleSheet("color:white;font-size:15px;");
    music_name->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    music_name->setText(QObject::tr("黑色毛衣-周杰伦"));


    //设置进度条
    QVBoxLayout *slider_layout = new QVBoxLayout();
    slider_layout->setSpacing(0);

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->setStyleSheet(
        "QSlider::groove:horizontal {"//设置轨道样式
        "border: 1px solid #999999;"
        "height: 8px;"
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
        "margin: 2px 0;"//设置上下边距
        "}"
        "QSlider::handle:horizontal {"//设置滑块样式
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
        "border: 1px solid #5c5c5c;"
        "width: 18px;"
        "margin: -2px 0;"
        "border-radius: 3px;"//设置边角半径，使角看起来圆润
        "}"
    );

    slider_layout->addWidget(slider);


    //布置按钮
    QHBoxLayout *btn_layout = new QHBoxLayout();
    for (int i = 0; i < 5; ++i) {
        QPushButton *btn1 = new QPushButton();
        QString backgroundimg;
        if(i == 0){
            backgroundimg = "url(:icon/danqu.png)";
        }else if(i == 1){
            backgroundimg = "url(:icon/back.png)";
        }else if(i == 2){
            backgroundimg = "url(:icon/play.png)";
        }else if(i == 3){
            backgroundimg = "url(:icon/foward.png)";
        }else if(i == 4){
            backgroundimg = "url(:icon/voice.png)";
        }
        //每次调用setStyleSheet都会覆盖上一次的setStyleSheet，所以尽可能整合为一个
        btn1->setStyleSheet("QPushButton {"
                        "background-color: SlateGray;color:silver;font-size:30px;font-weight: bold;border:0.5px solid DimGray; "
                        "background-image:" + backgroundimg + ";"
                        "background-repeat:no-repeat;"
                        "background-position:center;"
                        "}"
                        "QPushButton:hover {"
                        "background-color: DarkSlateGray;color:silver;font-size:30px;font-weight: bold;border:1px solid DimGray; "
                        "background-repeat:no-repeat;"
                        "background-position:center;"
                        "}"
                        "QPushButton:pressed {"
                        "background-color: DarkSlateGray;color:silver;font-size:30px;font-weight: bold;border:3px solid DimGray; "
                        "background-repeat:no-repeat;"
                        "background-position:center;"
                        "}");


        btn1->setFixedSize(40,40);
        btn_layout->addWidget(btn1);
    }
    ctrl_biglayout->addWidget(music_info);
    ctrl_biglayout->addStretch();
    //这里需要一个进度条组件
    ctrl_biglayout->addLayout(slider_layout);
    ctrl_biglayout->addStretch();
    ctrl_biglayout->addLayout(btn_layout);



}





//--------------------------------------------------------------------绘制界面 结束--------------------------------------------------------------------

//--------------------------------------------------------------------动态界面 开始--------------------------------------------------------------------


void MainWindow::settitle(QString window_title)
{
    title_text->setText(window_title);
}







//--------------------------------------------------------------------动态界面 结束--------------------------------------------------------------------


//--------------------------------------------------------------------逻辑相关 开始--------------------------------------------------------------------


//--------------------------------------------------------------------逻辑相关 结束--------------------------------------------------------------------













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
    music_name = nullptr;
    cur_song = nullptr;
    music_pic = nullptr;
    nowtime = nullptr;
    endtime = nullptr;


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
    setright1(right);
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

    music_pic = new QLabel(music_info);
    music_pic->setFixedSize(45,45);
    music_pic->move(3,2);
    music_pic->setScaledContents(true);
    QPixmap music_img(":icon/music_demopic.jpg");
    music_pic->setPixmap(music_img);


    music_name = new QLabel(music_info);
    music_name->setFixedSize(150,50);
    music_name->move(50,0);
    music_name->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    music_name->setStyleSheet("color:white;font-size:15px;");
    music_name->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    music_name->setText("示例歌名-示例歌手");


    //设置进度条
    QHBoxLayout *slider_layout = new QHBoxLayout();
    //slider_layout->setSpacing(0);

    nowtime = new QLabel();
    nowtime->setStyleSheet("color:yellow;font-size:10px;");
    nowtime->setText("00:00");
    slider_layout->addWidget(nowtime);



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

    endtime = new QLabel();
    endtime->setStyleSheet("color:yellow;font-size:10px;");
    endtime->setText("00:00");
    slider_layout->addWidget(endtime);

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

void MainWindow::setright1(QVBoxLayout *right)
{
    QWidget *r_main_info = new QWidget(center);
    r_main_info->setFixedHeight(250);
    r_main_info->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    r_main_info->setStyleSheet("border: 1px solid black;");
    right->addWidget(r_main_info);



    //构造一个滚动条
    QScrollArea *scroll = new QScrollArea(center);
    scroll->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    scroll->setWidgetResizable(true);
    right->addWidget(scroll);

    QWidget *inscroll_wid = new QWidget(scroll);
    inscroll_wid->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    scroll->setWidget(inscroll_wid);

    QVBoxLayout *table_list = new QVBoxLayout(inscroll_wid);
    table_list->setContentsMargins(0,0,0,0);
    table_list->setSpacing(0);

    //创建表头
    QHBoxLayout *head_layout = new QHBoxLayout();
    head_layout->setContentsMargins(0,0,0,0);

    for (int i = 0; i < 5; ++i) {
        QLabel *label_head = new QLabel();
        label_head->setAlignment(Qt::AlignCenter);
        label_head->setFixedHeight(30);
        label_head->setStyleSheet("border:1px solid gray;color:black;font-size:25px;font-weight: bold;");
        if(i == 0){
            label_head->setText("序号");
            head_layout->addWidget(label_head,1);
        }else if(i == 1){
            label_head->setText("歌曲");
            head_layout->addWidget(label_head,2);
        }else if(i == 2){
            label_head->setText("操作");
            head_layout->addWidget(label_head,2);
        }else if(i == 3){
            label_head->setText("歌手");
            head_layout->addWidget(label_head,2);
        }else if(i == 4){
            label_head->setText("收藏");
            head_layout->addWidget(label_head,1);
        }

    }
    table_list->addLayout(head_layout);

    //在一个函数中单独处理列表内容
    setlist1(table_list);
    table_list->addStretch();
}

void MainWindow::setlist1(QVBoxLayout *right, song_list *songlist)
{
    bool iscolor = false;
    for (int line = 0; line < 20; ++line) {
        QString back_color = "";
        if(iscolor){
            back_color = "silver";
            iscolor = false;
        }else{
            back_color = "white";
            iscolor = true;
        }

        QHBoxLayout *row = new QHBoxLayout();
        row->setContentsMargins(0,0,0,0);
        for (int i = 0; i < 5; ++i) {
            QLabel *label_head = new QLabel();
            label_head->setAlignment(Qt::AlignCenter);
            label_head->setFixedHeight(30);
            label_head->setStyleSheet("border:1px solid lightgray;color:black;font-size:20px;background-color:"+back_color+";");
            if(i == 0){
                label_head->setText("1");
                row->addWidget(label_head,1);
            }else if(i == 1){
                label_head->setText("示例歌名");
                row->addWidget(label_head,2);
            }else if(i == 2){
                label_head->setText("操作");
                row->addWidget(label_head,2);
            }else if(i == 3){
                label_head->setText("示例歌手");
                row->addWidget(label_head,2);
            }else if(i == 4){
                label_head->setText("❤");
                row->addWidget(label_head,1);
            }
        }
        right->addLayout(row);
    }
}

void MainWindow::setright2(QVBoxLayout *right)
{

}





//--------------------------------------------------------------------绘制界面 结束--------------------------------------------------------------------

//--------------------------------------------------------------------动态界面 开始--------------------------------------------------------------------


void MainWindow::settitle(QString window_title)
{
    title_text->setText(window_title);
}

void MainWindow::set_songinfo()
{
    if(cur_song!=nullptr){
        //设置歌曲信息
        QPixmap music_img(":icon/music_demopic.jpg");
        music_pic->setPixmap(cur_song->getsong_pic());
        music_name->setText(cur_song->getsongname() + "-" + cur_song->getsinger());
        //设置进度条时间
        nowtime->setText(to_time(cur_song->getlast_time()));
        endtime->setText(to_time(cur_song->getsong_time()));
    }
}

//将秒转换为分秒
QString MainWindow::to_time(int second_time)
{
    int minute = second_time/60;
    int remainingSeconds =second_time%60;
    //设定最小宽度为2，当位数不足是用0补齐
    return QString("%1:%2").arg(minute,2,10,QChar('0')).arg(remainingSeconds,2,10,QChar('0'));
}

//将分秒转换为秒
int MainWindow::of_time(QString minute_time)
{
    QStringList strs = minute_time.split(":");
    int minutes = strs[0].toInt();
    int seconds = strs[1].toInt();
    return minutes * 60 + seconds;
}







//--------------------------------------------------------------------动态界面 结束--------------------------------------------------------------------


//--------------------------------------------------------------------逻辑相关 开始--------------------------------------------------------------------


//--------------------------------------------------------------------逻辑相关 结束--------------------------------------------------------------------













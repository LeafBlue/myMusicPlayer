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
    list_pic = nullptr;
    list_name = nullptr;
    scroll = nullptr;
    right = nullptr;
    ctrl_wid = nullptr;

    audiooutput = new QAudioOutput(this);


    //当前音乐
    cur_song = nullptr;
    filetool = new file_tool();

    create_files();
    get_map_data();


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
    center->setStyleSheet("background-color: White;");

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
    //word_wid->setStyleSheet("background-color:Blue;");
    word_wid->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    work_area->addWidget(word_wid);

    QHBoxLayout *in_wid = new QHBoxLayout(word_wid);

    QVBoxLayout *left = new QVBoxLayout();
    left->setContentsMargins(0,0,0,0);
    left->setSpacing(0);
    in_wid->addLayout(left,1);

    right = new QVBoxLayout();
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


        if(i == 0){
            QLabel *left_label = new QLabel(in_scroll);

            left_label->setText("我的音乐");
            left_label->setStyleSheet("border:1px solid lightgray;font-size:16px;color:gray;");
            left_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            left_label->setFixedHeight(50);
            left_label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
            in_scroolwid->addWidget(left_label);
        }
        else if(i == 5){
            QLabel *left_label = new QLabel(in_scroll);

            left_label->setText("创建的歌单");
            left_label->setStyleSheet("border:1px solid lightgray;font-size:16px;color:gray;");
            left_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            left_label->setFixedHeight(50);
            left_label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
            in_scroolwid->addWidget(left_label);
        }
        else{
            songlistlabel *thislabel = new songlistlabel();
            //在此处为特别列表设置特别id
            if(i == 1){
                thislabel->setText("  我的收藏");
            }else if(i == 2){
                thislabel->setText("  本地音乐");
            }else if(i == 3){
                thislabel->setText("  最近播放");
            }else if(i == 4){
                thislabel->setText("  全部音乐");
            }
            thislabel->setsonglistid(i - 1);
            connect(thislabel,&songlistlabel::leftclick,this,[this,thislabel](){
                //执行左键点击函数
                set_songlist_info(thislabel->getsonglistid());
            });
            connect(thislabel,&songlistlabel::rightclick,this,[this](){
                //右键点击

            });
            in_scroolwid->addWidget(thislabel);
        }

    }

    set_songlist_menu(in_scroolwid,in_scroll);
    setright1();
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

    //做个遮罩处理图片
    QBitmap mask(music_pic->size());
    mask.fill(Qt::color0);
    QPainter painter(&mask);
    painter.setBrush(Qt::color1);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QRect(0,0,music_pic->width(),music_pic->height()));
    painter.end();
    music_pic->setMask(mask);



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
    ctrl_wid = new wid_ctrl();

    ctrl_biglayout->addWidget(music_info);
    ctrl_biglayout->addStretch();
    //这里需要一个进度条组件
    ctrl_biglayout->addLayout(slider_layout);
    ctrl_biglayout->addStretch();
    ctrl_biglayout->addWidget(ctrl_wid);



}

void MainWindow::setright1(int songlist_id)
{

    //获得这个歌单的基本信息
    song_list* this_songlist = getsonglistbyid(songlist_v,songlist_id);



    QWidget *r_main_info = new QWidget(center);
    r_main_info->setFixedHeight(180);
    r_main_info->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    r_main_info->setStyleSheet("background-color:lightgray;");

    //这里展示歌单资料
    list_pic = new QLabel(r_main_info);

    list_pic->setFixedSize(100,100);
    list_pic->move(50,50);
    list_pic->setScaledContents(true);
    if(this_songlist != nullptr && this_songlist->getlistpic().size()>0){
        QPixmap list_img(this_songlist->getlistpic());
        list_pic->setPixmap(list_img);
    }else{
        QPixmap list_img(":icon/music_demopic.jpg");
        list_pic->setPixmap(list_img);
    }



    //做个遮罩处理图片
    QBitmap mask(list_pic->size());
    mask.fill(Qt::color0);
    QPainter painter(&mask);
    painter.setBrush(Qt::color1);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QRect(0,0,list_pic->width(),list_pic->height()));
    painter.end();
    list_pic->setMask(mask);

    //做个显示文字的
    //就这样显示一下吧，反正也没有最大化
    list_name = new QLabel(r_main_info);
    list_name->setFixedSize(500,100);
    list_name->move(200,50);
    list_name->setStyleSheet("border:none;color:white;");

    QString songlistname = "新建歌单";
    QString songlistinfo = "该歌单很神秘，没有任何介绍";
    if(this_songlist != nullptr){
        songlistname = this_songlist->getlistname().size()>0?this_songlist->getlistname():"新建歌单";
        songlistinfo = this_songlist->getlistinfo().size()>0?this_songlist->getlistinfo():"该歌单很神秘，没有任何介绍";
    }
    list_name->setText(QString("<h1>%1</h1><p style='font-size:16px;'>%2</p>").arg(songlistname).arg(songlistinfo));



    //这里做一个动画效果的梦


    right->addWidget(r_main_info);

    //需要加几个按钮，作为对歌单的处理
    QWidget *r_list_btn = new QWidget(center);
    r_list_btn->setFixedHeight(50);
    r_list_btn->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    r_list_btn->setStyleSheet("background-color:lightgray;");
    QHBoxLayout *list_btn_layout = new QHBoxLayout(r_list_btn);


    list_btn_layout->addSpacing(50);
    for (int btnnum = 0; btnnum < 3; ++btnnum) {
        QPushButton *btn1 = new QPushButton();
        if(btnnum == 0){
            btn1->setText(QObject::tr("添加音乐"));
            connect(btn1,&QPushButton::clicked,[this,songlist_id](){
                addmusicfromfile(songlist_id);
            });
        }else if(btnnum == 1){
            btn1->setText(QObject::tr("播放全部"));
        }else if(btnnum == 2){
            btn1->setText(QObject::tr("批量操作"));
        }
        btn1->setFixedSize(100,30);
        btn1->setStyleSheet("QPushButton {background-color: SlateGray;color:silver;font-size:20px;font-weight: bold;border:0.5px solid DimGray; }"
                            "QPushButton:hover {background-color: DarkSlateGray;color:silver;font-size:20px;font-weight: bold;border:0.5px solid DimGray; }"
                            "QPushButton:pressed {background-color: DarkSlateGray;color:silver;font-size:18px;font-weight: bold;border:2px solid DimGray; }");


        list_btn_layout->addWidget(btn1);
    }
    list_btn_layout->addStretch();
    right->addWidget(r_list_btn);

    setlist1(this_songlist);

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
        if(cur_song->getsong_pic().size()>0){
            music_pic->setPixmap(cur_song->getsong_pic());
        }else{
            music_pic->setPixmap(music_img);
        }

        music_name->setText(cur_song->getsongname() + "-" + cur_song->getsinger());
        //设置进度条时间
        nowtime->setText(to_time(0));
        endtime->setText(to_time(cur_song->getsong_time()));
    }
}

//设置歌单信息
void MainWindow::set_songlist_info(int songlist_id)
{
    song_list* this_songlist = getsonglistbyid(songlist_v,songlist_id);

    if(this_songlist != nullptr && this_songlist->getlistpic().size()>0){
        QPixmap list_img(this_songlist->getlistpic());
        list_pic->setPixmap(list_img);
    }else{
        QPixmap list_img(":icon/music_demopic.jpg");
        list_pic->setPixmap(list_img);
    }
    QString songlistname = "新建歌单";
    QString songlistinfo = "该歌单很神秘，没有任何介绍";
    if(this_songlist != nullptr){
        songlistname = this_songlist->getlistname().size()>0?this_songlist->getlistname():"新建歌单";
        songlistinfo = this_songlist->getlistinfo().size()>0?this_songlist->getlistinfo():"该歌单很神秘，没有任何介绍";
    }
    list_name->setText(QString("<h1>%1</h1><p style='font-size:16px;'>%2</p>").arg(songlistname).arg(songlistinfo));

    setlist1(this_songlist);
}

void MainWindow::set_songlist_menu(QVBoxLayout *in_scroolwid,QWidget *in_scroll)
{
    songlist_v = filetool->select_list();
    if(songlist_v.size()>4){
        for (int i = 4; i < songlist_v.size(); ++i) {
            QLabel *left_label = new QLabel(in_scroll);
            left_label->setProperty("listid",songlist_v.at(i).getlistnum());
            left_label->setText("  " + songlist_v.at(i).getlistname());
            left_label->setStyleSheet("border:1px solid lightgray;font-size:18px;color:black;font-weight: bold;");
            left_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            left_label->setFixedHeight(50);
            left_label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

            in_scroolwid->addWidget(left_label);
        }
    }
    //只会执行一次
    if(songlist_v.size() == 0){
        //增加基础列表到文件：0 我的收藏，1 本地音乐 2 最近播放 3 全部音乐
        song_list song1;
        song1.setlist(0,"我的收藏","","");
        songlist_v.push_back(song1);
        song_list song2;
        song2.setlist(1,"本地音乐","","");
        songlist_v.push_back(song2);
        song_list song3;
        song3.setlist(2,"最近播放","","");
        songlist_v.push_back(song3);
        song_list song4;
        song4.setlist(3,"全部音乐","","");
        songlist_v.push_back(song4);

        filetool->rewritelist(songlist_v);
        songlist_v = filetool->select_list();

        filetool->createsonglist(0);
        filetool->createsonglist(1);
        filetool->createsonglist(2);
        filetool->createsonglist(3);
    }

}

void MainWindow::setlist1(song_list *songlist,int page)
{

    //在重新初始化此组件前，先将原来的妥善处理
    //这里的做法颇有点拖泥带水，但更好的做法需要更麻烦的操作
    if (scroll) {
        scroll->deleteLater(); // 安全删除 QScrollArea 及其子控件
        scroll = nullptr;      // 避免悬空指针
    }

    scroll = new QScrollArea(center);
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

    bool iscolor = false;
    if(songlist!=nullptr){
        int this_songlistid = songlist->getlistnum();

        //清空重新赋值
        cur_list.clear();
        cur_list = filetool->getsonglist(this_songlistid);

        //做分页处理，每页20条
        size_t data_num = cur_list.size();
        if(data_num > 0){
            for (int line = 0; line < 20; ++line) {
                int index = 20 * (page - 1) + line;
                if(index > data_num - 1){
                    break;
                }
                song_info cur_song_ = map[cur_list[index]];

                QString back_color = "";
                if(iscolor){
                    back_color = "silver";
                    iscolor = false;
                }else{
                    back_color = "white";
                    iscolor = true;
                }

                wid_songlist *wid_row = new wid_songlist();
                wid_row->setFixedHeight(30);
                wid_row->setsong_id(cur_song_.getsongid());
                wid_row->setStyleSheet("wid_songlist{background-color:"+back_color+";}"
                                       "wid_songlist:hover{background-color:MediumPurple;}");
                //绑定双击事件
                connect(wid_row,&wid_songlist::doubleclick,[this](){
                    play_music();
                });


                QHBoxLayout *row = new QHBoxLayout(wid_row);
                row->setContentsMargins(0,0,0,0);
                row->setSpacing(0);


                for (int i = 0; i < 5; ++i) {
                    QLabel *label_head = new QLabel();
                    label_head->setAlignment(Qt::AlignCenter);
                    label_head->setFixedHeight(30);
                    //label_head->setAttribute(Qt::WA_TransparentForMouseEvents, true);
                    label_head->setStyleSheet("QLabel{border:1px solid lightgray;color:black;font-size:20px;background-color: transparent;}");
                    if(i == 0){
                        label_head->setText(QString::number(cur_song_.getsongid() + 1));
                        row->addWidget(label_head,1);
                    }else if(i == 1){
                        label_head->setText(cur_song_.getsongname());
                        row->addWidget(label_head,2);
                    }else if(i == 2){
                        //此功能待完善
                        label_head->setText("操作");
                        row->addWidget(label_head,2);
                    }else if(i == 3){
                        label_head->setText(cur_song_.getsinger());
                        row->addWidget(label_head,2);
                    }else if(i == 4){
                        //此功能待完善
                        label_head->setText("❤");
                        row->addWidget(label_head,1);
                    }
                }
                table_list->addWidget(wid_row);
            }

            //生成一个分页效果
            if(data_num >20){
                QHBoxLayout *row = new QHBoxLayout();
                row->setContentsMargins(0,0,0,0);
                int pages = (data_num / 20) + 1;
                if(pages <= 10){
                    for (int p = 0; p < pages; ++p) {
                        QLabel *label_head = new QLabel();
                        label_head->setAlignment(Qt::AlignCenter);
                        label_head->setFixedSize(20,20);
                        //先这么写
                        if(p+1 == page){
                            label_head->setStyleSheet("color:white;font-size:15px;background-color:Blue;");
                        }else{
                            label_head->setStyleSheet("color:white;font-size:15px;background-color:LightBlue;");
                        }


                        label_head->setText(QString::number(p + 1));
                        row->addWidget(label_head);
                    }
                }else{
                    //当分页超过10
                    int thispage = 1;
                    bool setellpsis = false;
                    while(thispage <= pages){

                        QLabel *label_head = new QLabel();
                        label_head->setAlignment(Qt::AlignCenter);
                        label_head->setFixedSize(20,20);


                        if(thispage == 1 || thispage == pages|| std::abs(thispage - page) <= 2){
                            label_head->setText(QString::number(thispage));
                            setellpsis = false;

                            if(thispage == page){
                                label_head->setStyleSheet("color:white;font-size:15px;background-color:Blue;");
                            }else{
                                label_head->setStyleSheet("color:white;font-size:15px;background-color:LightBlue;");
                            }
                        }
                        else{
                            if(!setellpsis){
                                label_head->setText("……");
                                setellpsis = true;
                            }
                        }
                        row->addWidget(label_head);
                    }
                }
                table_list->addLayout(row);
            }
        }


    }

    table_list->addStretch();


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
//取到全局变量数据
void MainWindow::get_map_data()
{
    map = filetool->select_song();
}

void MainWindow::create_files()
{
    filetool->create_infolder();
    filetool->create_songfile();
    filetool->create_listfile();
}

void MainWindow::addmusicfromfile(int listid)
{
    QString filename = QFileDialog::getOpenFileName(this,QObject::tr("打开文件"),"D:",QObject::tr("音频文件(*.mp3 *.wav *.aac *.m4a)"));


    player.setSource(QUrl::fromLocalFile(filename));

    QFileInfo fileinfo(filename);

    QObject::connect(&player,&QMediaPlayer::mediaStatusChanged,[&,listid,fileinfo,filename](QMediaPlayer::MediaStatus status){

        if(status == QMediaPlayer::LoadedMedia){

            const QMediaMetaData metadata = player.metaData();


            QString song_name = metadata.value(QMediaMetaData::Title).toString();
            song_name = song_name.size()>0?song_name:fileinfo.baseName();

            QString singer = metadata.value(QMediaMetaData::Author).toString();
            QString song_album = metadata.value(QMediaMetaData::AlbumTitle).toString();
            int song_time = metadata.value(QMediaMetaData::Duration).toInt() / 1000;

            //获取id
            int song_id = map.size();
            song_info info;
            info.setSong(song_id,song_name,singer,filename,song_time);
            map.insert(song_id,info);
            //添加入文件理论上应该写入文件一次，否则其他的歌单读不到
            //需要添加的地方：本地音乐，全部音乐
            //需要一个在文件末行添加的功能
            filetool->writesong(info);
            filetool->add_one_data(1,song_id);
            filetool->add_one_data(3,song_id);
            if(listid != 1 && listid != 3){
                filetool->add_one_data(listid,song_id);
            }
            //重新加载当页歌曲
            set_songlist_info(listid);

        }
    });
}

void MainWindow::play_music()
{
    if(cur_song == nullptr){
        if(cur_list.size() > 0){
            cur_song = &(map[cur_list[0]]);
        }else{
            return;
        }
    }
    QString filename = cur_song->getsong_filename();

    set_songinfo();
    if(!QFile::exists(filename)){
        qDebug("file not exist.");
        return;
    }

    player.setSource(QUrl::fromLocalFile(filename));
    connect(&player,&QMediaPlayer::mediaStatusChanged,[&](QMediaPlayer::MediaStatus status){
        if(status == QMediaPlayer::LoadedMedia){

            player.setAudioOutput(audiooutput);
            audiooutput->setVolume(0.5);
            player.play();
        }
    });
}

//--------------------------------------------------------------------逻辑相关 结束--------------------------------------------------------------------

//--------------------------------------------------------------------播放控制 开始--------------------------------------------------------------------




//--------------------------------------------------------------------播放控制 结束--------------------------------------------------------------------









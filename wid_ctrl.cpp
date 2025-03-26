#include "wid_ctrl.h"

wid_ctrl::wid_ctrl(QWidget *parent)
    : QWidget{parent}
{
    sequece_ = 1;//1,顺序 2 单体 3随机
    play_status = false;
    showvoice = false;

    QHBoxLayout *btn_layout = new QHBoxLayout(this);

    play_sequece = new QPushButton(this);
    getstyle(play_sequece,"url(:icon/shunxu.png)");
    btn_layout->addWidget(play_sequece);

    connect(play_sequece,&QPushButton::clicked,[&](){
        if(sequece_ == 1){
            sequece_ = 2;
            getstyle(play_sequece,"url(:icon/danqu.png)");
        }
        else if(sequece_ == 2){
            sequece_ = 3;
            getstyle(play_sequece,"url(:icon/suiji.png)");
        }
        else if(sequece_ == 3){
            sequece_ = 1;
            getstyle(play_sequece,"url(:icon/shunxu.png)");
        }
    });

    prev_ = new QPushButton(this);
    getstyle(prev_,"url(:icon/back.png)");
    btn_layout->addWidget(prev_);

    connect(prev_,&QPushButton::clicked,[&](){
        emit do_prev();
    });

    play_pause = new QPushButton(this);
    getstyle(play_pause,"url(:icon/play.png)");
    btn_layout->addWidget(play_pause);

    connect(play_pause,&QPushButton::clicked,[&](){
        if(this->play_status){
            getstyle(play_pause,"url(:icon/play.png)");
            this->play_status = false;
            emit do_pause();
        }else{
            getstyle(play_pause,"url(:icon/pause.png)");
            this->play_status = true;
            emit do_play();
        }
    });

    next_ = new QPushButton(this);
    getstyle(next_,"url(:icon/foward.png)");
    btn_layout->addWidget(next_);

    connect(next_,&QPushButton::clicked,[&](){
        emit do_next();
    });

    voice_novoice = new QPushButton(this);
    getstyle(voice_novoice,"url(:icon/voice.png)");
    btn_layout->addWidget(voice_novoice);

    connect(voice_novoice,&QPushButton::clicked,[&](){
        if(showvoice){
            showvoice = false;
        }else{
            showvoice = true;
        }
        emit show_voice();
    });

}

void wid_ctrl::getstyle(QPushButton *btn, const QString back_img)
{
    btn->setStyleSheet("QPushButton {"
                     "background-color: SlateGray;"
                     "border-image:" + back_img + " 5 5 5 5 stretch stretch;"
                        "}"
                        "QPushButton:hover {"
                        "background-color: DarkSlateGray; "
                        "border-image:" + back_img + " 5 5 5 5 stretch stretch;"
                        "}"
                        "QPushButton:pressed {"
                        "background-color: DarkSlateGray; "
                        "border-image:" + back_img + " 0 0 0 0 scale-down;"
                           "}");
    btn->setFixedSize(35,35);

}





void wid_ctrl::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);  // 初始化样式选项
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this); // 绘制样式表
}



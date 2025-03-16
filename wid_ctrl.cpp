#include "wid_ctrl.h"

wid_ctrl::wid_ctrl(QWidget *parent)
    : QWidget{parent}
{
    play_status = false;

    QHBoxLayout *btn_layout = new QHBoxLayout(this);

    play_sequece = new QPushButton(this);
    getstyle(play_sequece,"url(:icon/danqu.png)");
    btn_layout->addWidget(play_sequece);

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



#include "wid_songlist.h"

wid_songlist::wid_songlist(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_Hover);
}

void wid_songlist::setsong_id(int song_id)
{
    this->song_id = song_id;
}

int wid_songlist::getsong_id()
{
    return this->song_id;
}

void wid_songlist::setsong_list_id(int song_list_id)
{
    this->song_list_id = song_list_id;
}

int wid_songlist::getsong_list_id()
{
    return this->song_list_id;
}

void wid_songlist::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit doubleclick();
    }
    QWidget::mouseDoubleClickEvent(event);
}

void wid_songlist::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);  // 初始化样式选项
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this); // 绘制样式表
}

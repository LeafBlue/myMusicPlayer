#include "songlistlabel.h"

songlistlabel::songlistlabel() {
    this->setStyleSheet("QLabel { border:1px solid lightgray;font-size:18px;color:black;font-weight: bold; }"
                        "QLabel:hover { background-color: LightGray;border:1px solid lightgray;font-size:18px;color:black;font-weight: bold; }");
    this->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    this->setFixedHeight(50);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
}

int songlistlabel::getsonglistid()
{
    return this->songlist_id;
}

void songlistlabel::setsonglistid(int songlist_id)
{
    this->songlist_id = songlist_id;
}

void songlistlabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit leftclick();
    }
    QLabel::mousePressEvent(event);
}

void songlistlabel::contextMenuEvent(QContextMenuEvent *event)
{
    emit rightclick();
}

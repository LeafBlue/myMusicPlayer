#include "dialog_label.h"

dialog_label::dialog_label() {
    this->setFixedSize(200,40);
    this->setStyleSheet("QLabel{border:1px solid blue;background-color: white;font-size: 20px;}"
                        "QLabel:hover{background-color: #F0F8FF;}");

}

void dialog_label::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit leftclick();
    }
    QLabel::mousePressEvent(event);
}

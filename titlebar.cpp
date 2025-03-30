#include "titlebar.h"

TitleBar::TitleBar(QWidget *parent)
    : QWidget{parent}
{}

void TitleBar::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        // 记录鼠标按下时的初始位置
        m_dragPosition = event->globalPos() - this->window()->frameGeometry().topLeft();
        event->accept();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton) {
        // 根据鼠标移动的距离更新窗口位置
        this->window()->move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        // 鼠标释放时清空拖动状态
        m_dragPosition = QPoint();
        event->accept();
    }
}

void TitleBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);  // 初始化样式选项
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this); // 绘制样式表
}

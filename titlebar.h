#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include<QPaintEvent>
#include<QPainter>
#include<QStyle>
#include<QStyleOption>

class TitleBar : public QWidget
{
    Q_OBJECT
private:
    QPoint m_dragPosition;
public:
    explicit TitleBar(QWidget *parent = nullptr);

signals:

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event)override;
};

#endif // TITLEBAR_H

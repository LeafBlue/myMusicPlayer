#ifndef WID_SONGLIST_H
#define WID_SONGLIST_H

#include <QWidget>
#include<QObject>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QPainter>
#include<QStyle>

#include<QStyleOption>

class wid_songlist : public QWidget
{
    Q_OBJECT

private:
    int song_id;
public:
    explicit wid_songlist(QWidget *parent = nullptr);

    void setsong_id(int song_id);
    int getsong_id();

protected:
    void mouseDoubleClickEvent(QMouseEvent* event)override;

    void paintEvent(QPaintEvent *event)override;

signals:

    void doubleclick();
};

#endif // WID_SONGLIST_H

#ifndef WID_CTRL_H
#define WID_CTRL_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include<QLayout>
#include<QPaintEvent>
#include<QPainter>
#include<QStyle>
#include<QStyleOption>

class wid_ctrl : public QWidget
{
    Q_OBJECT
public:
    QPushButton *play_pause;
    bool play_status;//假设true时，状态为播放，显示为暂停

    QPushButton *next_;
    QPushButton *prev_;
    QPushButton *voice_novoice;
    QPushButton *play_sequece;

    int sequece_;

    bool showvoice;


    explicit wid_ctrl(QWidget *parent = nullptr);

    void getstyle(QPushButton *btn,const QString back_img);

protected:


    void paintEvent(QPaintEvent *event)override;

signals:

    void do_play();
    void do_pause();

    void do_next();
    void do_prev();

    void show_voice();

public slots:
};

#endif // WID_CTRL_H

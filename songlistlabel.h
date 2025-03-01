#ifndef SONGLISTLABEL_H
#define SONGLISTLABEL_H

#include <QLabel>
#include <QObject>
#include<QMouseEvent>
#include<QContextMenuEvent>
#include<QMenu>
#include<QAction>

class songlistlabel : public QLabel
{
    Q_OBJECT
public:


    songlistlabel();

    int getsonglistid();
    void setsonglistid(int songlist_id);

signals:
    //实现单击功能
    void leftclick();
    //实现右键功能
    void rightclick();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event)override;

private:
    int songlist_id;


};

#endif // SONGLISTLABEL_H

#ifndef DIALOG_LABEL_H
#define DIALOG_LABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include<QMouseEvent>
#include<QContextMenuEvent>

class dialog_label : public QLabel
{
    Q_OBJECT
public:
    dialog_label();
    int songlist_id;

signals:
    //实现单击功能
    void leftclick();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // DIALOG_LABEL_H

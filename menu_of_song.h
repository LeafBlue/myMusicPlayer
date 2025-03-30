#ifndef MENU_OF_SONG_H
#define MENU_OF_SONG_H

#include <QObject>
#include <QPushButton>
#include <QWidget>

class menu_of_song : public QPushButton
{
    Q_OBJECT
public:
    int menu_type;//1.播放 2.添加 3.删除
    menu_of_song();

    void getstyle(bool flag);
};

#endif // MENU_OF_SONG_H

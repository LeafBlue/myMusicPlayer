#ifndef FILE_TOOL_H
#define FILE_TOOL_H

#include <QObject>
#include"song_info.h"
#include"song_list.h"
#include<QDir>
#include<QStringList>

class file_tool : public QObject
{
    Q_OBJECT
private:
    QString projectpath;
    QString foldername;

    QString songfile;
    QString listfile;
public:
    explicit file_tool(QObject *parent = nullptr);

    //创建文件
    void create_infolder();

    void create_songfile();
    void create_listfile();

    void rewritesong(QVector<song_info>& songs);
    QVector<song_info> select_song();

    void rewritelist(QVector<song_list>& lists);
    QVector<song_list> select_list();


    void createsonglist(int& listid);
    void rewritesonglist(int& listid,QVector<int> songids);
    QVector<int> getsonglist(int& listid);
    void deletesonglist(int& listid);



signals:
};

#endif // FILE_TOOL_H

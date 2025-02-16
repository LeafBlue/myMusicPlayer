#ifndef FILE_TOOL_H
#define FILE_TOOL_H

#include <QObject>
#include"song_info.h"
#include"song_list.h"
#include<QDir>

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



    void add_sl(int& list_id);
    void delete_sl(int& listid);
    void addin_sl(int& listid,int& songid);
    void check_sl(int& listid,int& songid);//检查id是否已存在
    void delin_sl(int& listid,int& songid);
    QVector<int> select_listsong(int& listid,int& songid);


signals:
};

#endif // FILE_TOOL_H

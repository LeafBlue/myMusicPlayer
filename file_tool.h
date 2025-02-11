#ifndef FILE_TOOL_H
#define FILE_TOOL_H

#include <QObject>
#include"song_info.h"
#include"song_list.h"

class file_tool : public QObject
{
    Q_OBJECT
public:
    explicit file_tool(QObject *parent = nullptr);

    //void save_allsong();
    //创建
    void create_allsongfile();
    void create_songlistfile();
    void create_listfile();

    //存储歌曲所有信息
    void save_songinall(song_info& song);
    //只存储歌曲编号
    void save_songinlist(song_info& song,int list_num);
    //存储歌单信息，开始时只导入所需音乐，只有查询时再导入歌单信息
    void save_list();





signals:
};

#endif // FILE_TOOL_H

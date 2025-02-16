#include "file_tool.h"

file_tool::file_tool(QObject *parent)
    : QObject{parent}


{
    projectpath = QDir::currentPath();
    foldername = "song_files";

    songfile = QString("%1/%2/song.csv").arg(projectpath).arg(foldername);
    listfile = QString("%1/%2/list.csv").arg(projectpath).arg(foldername);
}



//创建文件路径
void create_infolder(){
    QDir dir;
    if(!dir.exists(foldername)){
        dir.mkpath(foldername);
    }
}

//创建song.csv用来存放所有歌曲
void file_tool::create_songfile(){
    QFile file(songfile);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return;
    }
    file.close();
}
void file_tool::create_listfile(){
    QFile file(listfile);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return;
    }
    file.close();
}

//清空文件重新写入
void file_tool::rewritesong(QVector<song_info>& songs){
    QFile file(songfile);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)){
        return;
    }
    QTextStream out(&file);
    for(const song_info &song:songs){
        QStringList row;
        row<<song.getsongid()<<song.getsongname()<<song.getsinger()<<song.getsong_filename()<<song.getsong_pic()<<song.getsong_time();
        out<<row.join(",")<<"\n";
    }
    file.close();

}
QVector<song_info> file_tool::select_song(){
    QFile file(songfile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return;
    }
    QTextStream in(&file);
    QVector<song_info> v;
    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList list = line.split(",");
        song_info song;
        song.setSong(list[0].toInt(),list[1],list[2],list[3],list[5].toInt(),list[4]);
        v.push_back(song);
    }
    file.close();
}

void file_tool::rewritelist(QVector<song_list>& lists){
    QFile file(listfile);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)){
        return;
    }
    QTextStream out(&file);
    for(const song_list &list:lists){
        QStringList row;
        //
        row<<
        out<<row.join(",")<<"\n";
    }
    file.close();
}
QVector<song_list> file_tool::select_list(){

}


void file_tool::add_sl(int& list_id);
void file_tool::delete_sl(int& listid);
void file_tool::addin_sl(int& listid,int& songid);
void file_tool::check_sl(int& listid,int& songid);//检查id是否已存在
void file_tool::delin_sl(int& listid,int& songid);
QVector<int> file_tool::select_listsong(int& listid,int& songid);

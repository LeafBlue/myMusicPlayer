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
void file_tool::create_infolder(){
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
        row<<QString::number(song.getsongid())<<song.getsongname()<<song.getsinger()<<song.getsong_filename()<<song.getsong_pic()<<QString::number(song.getsong_time());
        out<<row.join(",")<<"\n";
    }
    file.close();

}
QVector<song_info> file_tool::select_song(){
    QVector<song_info> v;
    QFile file(songfile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return v;
    }
    QTextStream in(&file);

    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList list = line.split(",");
        song_info song;
        song.setSong(list[0].toInt(),list[1],list[2],list[3],list[5].toInt(),list[4]);
        v.push_back(song);
    }
    file.close();
    return v;
}

void file_tool::rewritelist(QVector<song_list>& lists){
    QFile file(listfile);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)){
        return;
    }
    QTextStream out(&file);
    for(const song_list &list:lists){
        QStringList row;
        row<<QString::number(list.getlistnum())<<list.getlistname()<<list.getlistpic()<<list.getlistinfo();
        out<<row.join(",")<<"\n";
    }
    file.close();
}
QVector<song_list> file_tool::select_list(){
    QVector<song_list> v;
    QFile file(listfile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return v;
    }
    QTextStream in(&file);

    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList list = line.split(",");
        song_list s_list;
        s_list.setlist(list[0].toInt(),list[1],list[2],list[3]);
        v.push_back(s_list);
    }
    file.close();
    return v;
}


void file_tool::createsonglist(int& listid){
    QFile file(QString::number(listid) + ".csv");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return;
    }
    file.close();
}
void file_tool::rewritesonglist(int& listid,QVector<int> songids){
    QFile file(QString::number(listid) + ".csv");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)){
        return;
    }
    QTextStream out(&file);
    for(const int &songid:songids){
        out<<songid<<"\n";
    }
    file.close();
}
QVector<int> file_tool::getsonglist(int& listid){
    QVector<int> v;
    QFile file(QString::number(listid) + ".csv");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return v;
    }
    QTextStream in(&file);

    while(!in.atEnd()){
        QString line = in.readLine();
        v.push_back(line.toInt());
    }
    file.close();
    return v;
}
void file_tool::deletesonglist(int& listid){
    QString path = QString::number(listid) + ".csv";
    if(QFile::exists(path)){
        QFile::remove(path);
    }
}























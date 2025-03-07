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
void file_tool::rewritesong(QMap<int,song_info>& songs){
    QFile file(songfile);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)){
        return;
    }
    QTextStream out(&file);
    for(auto it = songs.begin();it != songs.end();++it){
        song_info& song = it.value();
        QStringList row;
        row<<QString::number(song.getsongid())<<song.getsongname()<<song.getsinger()<<song.getsong_filename()<<song.getsong_pic()<<QString::number(song.getsong_time());
        out<<row.join(",")<<"\n";

    }
    file.close();
}
//改为使用 QMap读取
QMap<int,song_info> file_tool::select_song(){
    QMap<int,song_info> map;
    QFile file(songfile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return map;
    }
    QTextStream in(&file);

    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList list = line.split(",");
        song_info song;
        song.setSong(list[0].toInt(),list[1],list[2],list[3],list[5].toInt(),list[4]);
        map.insert(list[0].toInt(),song);
    }
    file.close();
    return map;
}

//清空文件重新写入 用于非全局文件
void file_tool::rewritesong_v(QVector<song_info>& songs){
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
//用于非全局文件
QVector<song_info> file_tool::select_song_v(){
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
    std::sort(v.begin(),v.end(),[](song_list& a,song_list& b){
        return a.getlistnum()<b.getlistnum();
    });
    return v;
}


void file_tool::createsonglist(int listid){
    QFile file(QString("%1/%2/%3.csv").arg(projectpath).arg(foldername).arg(QString::number(listid)));
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return;
    }
    file.close();
}
void file_tool::rewritesonglist(int& listid,QVector<int> songids){
    QFile file(QString("%1/%2/%3.csv").arg(projectpath).arg(foldername).arg(QString::number(listid)));
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
    QFile file(QString("%1/%2/%3.csv").arg(projectpath).arg(foldername).arg(QString::number(listid)));
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return v;
    }
    QTextStream in(&file);

    while(!in.atEnd()){
        QString line = in.readLine();
        v.push_back(line.toInt());
    }
    file.close();
    std::sort(v.begin(),v.end(),[](int a,int b){
        return a< b;
    });
    return v;
}
void file_tool::deletesonglist(int& listid){
    QString path = QString("%1/%2/%3.csv").arg(projectpath).arg(foldername).arg(QString::number(listid));
    if(QFile::exists(path)){
        QFile::remove(path);
    }
}























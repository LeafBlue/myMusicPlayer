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
    if(file.exists()){
        return;
    }
    if(!file.open(QIODevice::Append|QIODevice::Text)){
        return;
    }
    file.close();
}
void file_tool::create_listfile(){
    QFile file(listfile);
    if(file.exists()){
        return;
    }
    if(!file.open(QIODevice::Append|QIODevice::Text)){
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
        row<<QString::number(song.getsongid())
            <<escapeCsvField(song.getsongname())
            <<escapeCsvField(song.getsinger())
            <<escapeCsvField(song.getsong_filename())
            <<escapeCsvField(song.getsong_pic())
            <<QString::number(song.getsong_time())
            <<QString::number(song.get_isexist());
        out<<row.join(",")<<"\n";

    }
    file.close();
}
//改为使用 QMap读取
std::pair<QMap<int,song_info>,QHash<QString,int>> file_tool::select_song(){
    std::pair<QMap<int,song_info>,QHash<QString,int>> p;
    QMap<int,song_info> map;
    QHash<QString,int> hash_;
    QFile file(songfile);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return p;
    }
    QTextStream in(&file);

    while(!in.atEnd()){
        QString line = in.readLine();
        QStringList list = line.split(",");
        song_info song;
        int isexist = list[6].toInt();
        song.setSong(list[0].toInt(),
                     unescapeCsvField(list[1]),
                     unescapeCsvField(list[2]),
                     unescapeCsvField(list[3]),
                     list[5].toInt(),
                     unescapeCsvField(list[4]),
                     isexist
                     );
        map.insert(list[0].toInt(),song);
        if(isexist == 1){
            //这里不会收录已删除的歌曲，这确保了已删除歌曲可以被重新上传
            hash_.insert(song.getsong_filename(),song.getsongid());
        }
    }
    file.close();

    p.first = map;
    p.second = hash_;
    return p;
}
//向存储歌曲的文件末尾增加一条数据
void file_tool::writesong(song_info& song){
    QFile file(songfile);
    if(!file.open(QIODevice::Append|QIODevice::Text)){
        return;
    }
    QTextStream out(&file);
    QStringList row;
    row<<QString::number(song.getsongid())
        <<escapeCsvField(song.getsongname())
        <<escapeCsvField(song.getsinger())
        <<escapeCsvField(song.getsong_filename())
        <<escapeCsvField(song.getsong_pic())
        <<QString::number(song.getsong_time())
        <<QString::number(song.get_isexist());
    out<<row.join(",")<<"\n";
    file.close();
}
//转义函数
QString file_tool::escapeCsvField(const QString& field){
    QString str = field;
    str.replace(",","丨1丨");
    str.replace("\"","丨2丨");
    str.replace("\n","丨3丨");
    return str;
}

//读取还原字符函数
QString file_tool::unescapeCsvField(const QString& field){
    QString str = field;
    str.replace("丨1丨",",");
    str.replace("丨2丨","\"");
    str.replace("丨3丨","\n");
    return str;
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
        row<<escapeCsvField(QString::number(song.getsongid()))
            <<escapeCsvField(song.getsongname())
            <<escapeCsvField(song.getsinger())
            <<escapeCsvField(song.getsong_filename())
            <<escapeCsvField(song.getsong_pic())
            <<escapeCsvField(QString::number(song.getsong_time()))
            <<QString::number(song.get_isexist());
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
        song.setSong(
            list[0].toInt(),
            unescapeCsvField(list[1]),
            unescapeCsvField(list[2]),
            unescapeCsvField(list[3]),
            list[5].toInt(),
            unescapeCsvField(list[4]),
            list[6].toInt());
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
        row<<escapeCsvField(QString::number(list.getlistnum()))
            <<escapeCsvField(list.getlistname())
            <<escapeCsvField(list.getlistpic())
            <<escapeCsvField(list.getlistinfo());
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
        s_list.setlist(list[0].toInt(),
                       unescapeCsvField(list[1]),
                       unescapeCsvField(list[2]),
                       unescapeCsvField(list[3]));
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
    if(file.exists()){
        return;
    }
    if(!file.open(QIODevice::Append|QIODevice::Text)){
        return;
    }
    file.close();
}
void file_tool::rewritesonglist(int listid,QVector<int> songids){
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
QVector<int> file_tool::getsonglist(int listid){
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
    return v;
}
void file_tool::deletesonglist(int& listid){
    QString path = QString("%1/%2/%3.csv").arg(projectpath).arg(foldername).arg(QString::number(listid));
    if(QFile::exists(path)){
        QFile::remove(path);
    }
}
//向对应歌单末尾添加一条数据
void file_tool::add_one_data(int listid,int addid){
    QFile file(QString("%1/%2/%3.csv").arg(projectpath).arg(foldername).arg(QString::number(listid)));

    if(!file.open(QIODevice::Append|QIODevice::Text)){
        return;
    }
    QTextStream out(&file);
    out<<addid<<"\n";
    file.close();
}

QSet<int> file_tool::getfavorite()
{
    QSet<int> set;
    QFile file(QString("%1/%2/0.csv").arg(projectpath).arg(foldername));
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        return set;
    }
    QTextStream in(&file);

    while(!in.atEnd()){
        QString line = in.readLine();
        set.insert(line.toInt());
    }
    file.close();
    return set;
}























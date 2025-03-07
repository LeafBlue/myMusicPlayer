#include"song_tool.h"

//使用二分法高效查找
song_list* getsonglistbyid(QVector<song_list>& v, int list_num)
{
    auto it = std::lower_bound(v.begin(),v.end(),list_num,[](song_list& s_a,int target_list_num){
        return s_a.getlistnum() < target_list_num;
    });
    if(it != v.end() && it->getlistnum() ==list_num){
        return &(*it);
    }
    return nullptr;
}


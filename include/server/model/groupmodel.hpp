#ifndef GROUPMODEL_H
#define GROUPMODEL_H
#include "group.hpp"
#include <string>
#include <vector>
using namespace std;
//维护群组信息的操作接口方法
class GroupModel
{
public:
    //创建群组
    bool createGroup(Group &group);
    //加入群组
    void addGroup(int userid,int groupid, string role);
    //查询用户所在群组信息
    vector<Group> queryGroups(int userid);
    //根据群组groupid查询群组用户id列表，用于群组聊天
    vector<int> queryGroupUsers(int userid,int groupid);

};

#endif
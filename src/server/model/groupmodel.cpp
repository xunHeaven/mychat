#include "groupmodel.hpp"
#include "mydb.h"

//创建群组
bool GroupModel::createGroup(Group &group)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into allgroup(groupname,groupdesc) values('%s','%s')", group.getName().c_str(),
            group.getDesc().c_str());
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            // 获取插入成功的group数据生成的主键id
            group.setID(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}
//加入群组
void GroupModel::addGroup(int userid,int groupid, string role)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into groupuser(groupid,userid,grouprole) values(%d,%d,'%s')",groupid,userid,role.c_str());
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }


}
//查询用户所在群组信息
vector<Group> GroupModel::queryGroups(int userid)
{
    /*1.先根据userid在groupuser表中查询出所属群组的信息
    2.再根据群组信息查询属于该组的所有用户userid，并且和User表进行多表联合查询，查出用户的详细信息
    */
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.groupname,a.groupdesc from allgroup a inner join groupuser b on b.groupid=a.id where b.userid=%d", userid);
    MySQL mysql;
    vector<Group> groupVec;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))!=nullptr)
            {
                Group group;
                group.setID(atoi(row[0]));
                group.setName(row[1]);
                group.setDesc(row[2]);
                groupVec.push_back(group);
            }
            mysql_free_result(res);
            
        }

    }
    for(Group &group:groupVec)
    {
        sprintf(sql,"select a.id,a.name,a.state,b.grouprole from User a inner join groupuser b on b.userid=a.id where b.groupid=%d",group.getID());
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))!=nullptr)
            {
                GroupUser user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                user.setRole(row[3]);
                //groupVec.push_back(group);
                group.getUsers().push_back(user);
            }
            mysql_free_result(res);
            
        }

    }
    return groupVec;

}
//根据群组groupid查询群组用户id列表，用于群组聊天
vector<int> GroupModel::queryGroupUsers(int userid,int groupid)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select userid from groupuser where groupid=%d and userid != %d",groupid, userid);
    MySQL mysql;
    vector<int> idVec;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))!=nullptr)
            {
                idVec.push_back(atoi(row[0]));
            }
            mysql_free_result(res);
            
        }

    }
    return idVec;

}
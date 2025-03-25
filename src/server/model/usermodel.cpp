#include "usermodel.hpp"
#include "mydb.h"
#include <iostream>
using namespace std;
// user增加方法
bool UserModel::insert(User &user)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into User(name,password,state) values('%s','%s','%s')", user.getName().c_str(),
            user.getPassword().c_str(), user.getState().c_str());
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            // 获取插入成功的用户数据生成的主键id
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}
User UserModel::query(int id)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "select * from User where id=%d", id);
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            // 获取插入成功的用户数据生成的主键id
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPassword(row[2]);
                user.setState(row[3]);
                mysql_free_result(res);
                return user;
            }
        }
    }
    return User();
}
// 更新用户状态信息
bool UserModel::updateState(User user)
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "update User set state='%s' where id=%d", user.getState().c_str(),user.getId());
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            // 如果更新成功
            //user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}
//重置用户的状态信息
void UserModel::resetState()
{
    // 组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "update User set state='offline' where state='online'");
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }

}
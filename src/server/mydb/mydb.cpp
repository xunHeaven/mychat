#include "mydb.h"
#include<muduo/base/Logging.h>
//数据库配置信息
static string server="127.0.0.1";
static string user="root";
static string password="yangxun";
static string dbname="chat";
//初始化数据库连接
MySQL::MySQL()
{
    _conn=mysql_init(nullptr);
}
//释放数据库连接资源
MySQL::~MySQL()
{
    if(_conn!=nullptr)
    {
        mysql_close(_conn);
    }
}
//连接数据库
bool MySQL::connect()
{
    MYSQL *p=mysql_real_connect(_conn,server.c_str(),user.c_str(),password.c_str(),dbname.c_str(),3306,nullptr,0);
    if(p!=nullptr)
    {
        //C和C++默认编码是ASCII码，如果不设置，从mysql上读出的中文数据会显示为“？？？”
        mysql_query(_conn,"set names gbk");
        LOG_INFO<<"connect mysql success!";
    }
    else
    {
        LOG_INFO<<"connect mysql failed!";
    }
    return p;
}
//更新操作
bool MySQL::update(string sql)
{
    //注意：操作成功返回0，失败则为非0
    if(mysql_query(_conn,sql.c_str()))
    {
        LOG_INFO<<__FILE__<<":"<<__LINE__<<":"<<sql<<" 更新失败!";
        return false;
    }
    LOG_INFO<<__FILE__<<":"<<__LINE__<<":"<<sql<<" 更新成功!";
    return true;
}
//查询操作
MYSQL_RES* MySQL::query(string sql)
{
    if(mysql_query(_conn,sql.c_str()))
    {
        LOG_INFO<<__FILE__<<":"<<__LINE__<<":"<<sql<<"查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}
//获取连接
MYSQL* MySQL::getConnection()
{
    return _conn;
}
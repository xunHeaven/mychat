#ifndef CHATSERVER_H
#define CHATSERVER_H
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <string>
using namespace muduo;
using namespace muduo::net;
//聊天服务器主类
class ChatServer{
public:
    //初始化聊天服务对象
    ChatServer(EventLoop* loop,const InetAddress &listenAddr,const string &nameArg );

    //启动服务
    void start();
private:
    //上报链接相关信息的回调函数
    void onConnection(const TcpConnectionPtr &conn);
    //上报读写事件相关信息的回调函数
    void onMessage(const TcpConnectionPtr& conn,Buffer * buffer, Timestamp time);
    TcpServer _server;
    EventLoop *_loop;

};
#endif
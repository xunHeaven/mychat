# mychat
概述：集群聊天服务器和客户端。基于muduo网络库实现，mysql数据库存储用户数据，nginx配置负载均衡，redis实现消息队列。

数据库说明：
创建表：分别为用户表（User），好友列表(friend)，群组表(allgroup)，群组用户表(groupuser)，离线消息表(offlinemessage)。
数据库表的生成方式见createSql.txt文件。

操作说明：将项目下载或clone 到本地之后，先清空build文件夹的内容。接下来开始编译。
1.build目录：cmake ..
2.在build目录：make
3.生成的可执行文件在bin目录下。

文件说明：
1.include文件夹下的头文件在src文件夹下都有对应的.cpp文件。所以直接对src目录下的文件进行说明。
2.src/server下chatserver.cpp是网络模块的代码。
3..src/server下chatservice.cpp是业务模块的代码，服务器各种功能的实现放在该模块，
实现了注册、登录、聊天、加群、好友增删等功能。
4.src/server/mydb下存放的是mysql数据库操作的实现代码，包括数据库连接、更新、查询的功能。
5.src/server/model下存放的是数据库表的操作文件。包括对用户表的操作（usermodel.cpp），好友列表的操作（friendmodel.cpp）,
群组的操作（groupmodel.cpp）,离线消息表的操作（offlinemsgmodel.cpp）。
6.src/server/mydb下存放的是redis的操作文件。

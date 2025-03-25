cmake_minimum_required(VERSION 3.20)
project(mychat)

#配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
#配置最终可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#配置头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)#头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/client)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)#三方库
include_directories(${PROJECT_SOURCE_DIR}/include/server/mydb)#数据库操作的头文件
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)#数据操作
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)#数据操作

#加载子目录,源码在src下
add_subdirectory(src)
#ifndef GROUP_H
#define GROUP_H

#include "groupuser.hpp"
#include <vector>
#include <string>
using namespace std;

//Group 表的映射类
class Group
{
private:
    int id;
    string name;
    string desc;
    vector<GroupUser> users;
public:
    Group(int id=-1,string name="",string desc="")
    {
        this->id=id;
        this->name=name;
        this->desc=desc;
    }
    void setID(int id){this->id=id;}
    void setName(string name){this->name=name;}
    void setDesc(string desc){this->desc=desc;}

    int getID(){return this->id;}
    string getName(){return this->name;}
    string getDesc(){return this->desc;}
    vector<GroupUser> &getUsers(){return this->users;}
    
};




#endif
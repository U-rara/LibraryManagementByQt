#pragma once

#include "BookManagement.h"
#include "ReaderManagement.h"
#include "BorrowList.h"

class Admin
{
private:
    int account;       //管理员账号
    string password;   //管理员密码
    string name;       //管理员姓名
    int id;            //管理员工号
public:
    Admin(int id, int account ,string name ,string password="123"): account(account), password(password), name(name), id(id) {}
    Admin() {}
    ~Admin() {}
    bool Check(string pas)    //登陆密码验证
    {
        return password == pas;
    }
    int get_account()          //返回账号
    {
        return account;
    }
    string get_password()      //返回密码
    {
        return password;
    }
    int get_id()                //返回工号
    {
        return id;
    }
    string get_name()           //返回姓名
    {
        return name;
    }
    bool operator == (const Admin &admin)const          //对==进行操作符重载(否则list的remove方法报错)，用账号进行管理员比较
    {
        if (account == admin.account) {
            return true;
        } else {
            return false;
        }
    }
    void set_password(string pas)
    {
        password=pas;
    }
};

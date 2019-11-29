#pragma once

#include "BookManagement.h"
#include "ReaderManagement.h"
#include "BorrowListManagement.h"

class Admin
{
private:
    int account;       //管理员账号
    string password;   //管理员密码
    string name;       //管理员姓名
    int id;            //管理员工号
public:
    Admin(int account, string password, string name, int id): account(account), password(password), name(name), id(id) {}
    Admin() {}
    ~Admin() {}
    bool Check(string pas)    //登陆密码验证
    {
        return password == pas;
    }
    int get_account()       //返回账号
    {
        return account;
    }
    string get_password()      //返回密码
    {
        return password;
    }
    int get_id()        //返回工号
    {
        return id;
    }
    string get_name()       //返回姓名
    {
        return name;
    }
    bool operator==(const Admin &admin)const          //对==进行操作符重载(否则list的remove方法报错)，用账号进行管理员比较
    {
        if (account == admin.account) {
            return true;
        } else {
            return false;
        }
    }
    void ChangePas(string pas){
        password=pas;
    }
    void PermitBorrow(BorrowList &app)        //借书许可
    {
        app.AdminId=id;
        time_t timeNow;
        time(&timeNow);
        tm *p = localtime(&timeNow);
        app.borrowTime=*p;
        app.returnTime=*p;
        app.returnTime.tm_mon++;
    }
    void PermitReturn(BorrowList &app){
        bool overdue=app.IsOverdue();
        app.returned=true;

    }
};

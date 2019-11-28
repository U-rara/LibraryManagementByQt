#pragma once

#include "BookManagement.h"
#include "ReaderManagement.h"

class Admin
{
private:
    int account; //管理员账号
    string password;
    string name;
    int id; //工号
public:
    Admin(int account, string password, string name, int id): account(account), password(password), name(name), id(id) {}
    Admin() {}
    ~Admin() {}
    bool Check(string pas)
    {
        return password == pas;
    }
    int get_account()
    {
        return account;
    }
    string get_password()
    {
        return password;
    }
    int get_id()
    {
        return id;
    }
    string get_name()
    {
        return name;
    }
    bool operator==(const Admin &admin)const          //对==进行操作符重载(否则list的remove方法报错)，用ISBN进行书籍种类比较
    {
        if (account == admin.account) {
            return true;
        } else {
            return false;
        }
    }
};
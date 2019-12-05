#pragma once

#include <iostream>
#include <string.h>
#include <list>
using namespace std;

class Reader
{
private:
    long long id; //学号
    string name;
    int account; //读者证号，检索用
    string password;
    int totalBorrowedBooks;
    int curBorrowedBooks;
public:
    Reader(long long id, int account, string name, string password="123456",int totalBorrowedBooks = 0, int curBorrowedBooks = 0): id(id), name(name), account(account),password(password), totalBorrowedBooks(totalBorrowedBooks), curBorrowedBooks(curBorrowedBooks) {}
    Reader() {}
    ~Reader() {}
    bool operator==(const Reader &reader)const {         //对==进行操作符重载(否则list的remove方法报错)
        if (account == reader.account)
        {
            return true;
        } else
        {
            return false;
        }
    }
    long long get_id()
    {
        return id;
    }
    int get_account()
    {
        return account;
    }
    string get_name()
    {
        return name;
    }
    string get_password()
    {
        return password;
    }
    void set_password(string pas)
    {
        password=pas;
    }
    int get_totalBorrowedBooks()
    {
        return totalBorrowedBooks;
    }
    int get_curBorrowedBooks()
    {
        return curBorrowedBooks;
    }
    bool Check(string pas)
    {
        return pas==password;
    }
    void BorrowPermitted()
    {
        curBorrowedBooks++;
    }
    void ReturnPermitted()
    {
        curBorrowedBooks--;
        totalBorrowedBooks++;
    }
};

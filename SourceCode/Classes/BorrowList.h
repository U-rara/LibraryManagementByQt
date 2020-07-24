#pragma once

#include "Book.h"
#include "Reader.h"
#include "Admin.h"
#include <ctime>
class Admin;        //对Admin类进行前置声明，否则编译出错
class BorrowList
{
    friend Admin;           //对管理员声明友元，管理员具有最高权限
private:
    int borrowListId;       //借书单号
    int borrowerId;         //读者学号
    long long bookISBN;     //图书ISBN
    int AdminId;            //管理员工号 默认为0表示提出借书申请但未被许可
    tm borrowTime;          //借书时间
    tm returnTime;          //还书期限（1个月)
    bool returned;          //是否已经归还
public:
    bool operator==(const BorrowList &borrowList)const          //对==进行操作符重载(否则list的remove方法报错）
    {
        if (borrowListId == borrowList.borrowListId) {
            return true;
        } else {
            return false;
        }
    }
    BorrowList(int borrowListId, int borrowerId, long long bookISBN ,tm &time, int AdminId=0 ,bool returned = false): borrowListId(borrowListId), borrowerId(borrowerId) , bookISBN(bookISBN) , AdminId(AdminId), borrowTime(time), returnTime(time), returned(returned)
    {
        returnTime.tm_mon++;
        if(returnTime.tm_mon==12){
            returnTime.tm_mon=0;
            returnTime.tm_year++;
        }
    }
    BorrowList() {}
    ~BorrowList() {}
    int get_borrowerId()        //返回读者学号
    {
        return borrowerId;
    }
    int get_borrowListId()      //返回借书单号
    {
        return borrowListId;
    }
    long long get_bookISBN()    //返回图书ISBN
    {
        return bookISBN;
    }
    int get_adminId()           //返回管理员工号
    {
        return AdminId;
    }
    bool IsPermitted()          //返回许可状态
    {
        return AdminId;
    }
    string get_borrowTime()     //以格式化字符串返回借书时间
    {
        string time = asctime(&borrowTime);
        return time;
    }
    string get_returnTime()     //以格式化字符串返回还书期限
    {
        string time = asctime(&returnTime);
        return time;
    }
    tm* get_returnTime_tm()     //以指针返回还书期限
    {
        return &returnTime;
    }
    bool IsReturned()           //返回归还状态
    {
        return returned;
    }
    void PermitBorrow(int adminId)        //借书许可
    {
        AdminId=adminId;
        time_t timeNow;
        time(&timeNow);
        tm *p = localtime(&timeNow);
        borrowTime=*p;
        returnTime=*p;
        returnTime.tm_mon++;
        if(returnTime.tm_mon==12){
            returnTime.tm_mon=0;
            returnTime.tm_year++;
        }
    }
    void PermitReturn(){
        returned=true;
    }
//    void PermitReturn(BorrowList &app){
//        bool overdue=app.IsOverdue();
//        app.returned=true;

//    }
};

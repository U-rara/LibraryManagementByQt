#pragma once

#include "Book.h"
#include "Reader.h"
#include "Admin.h"
#include <ctime>

class BorrowList
{
private:
    int borrowListId;
    int borrowerId;
    long long bookISBN;
    int AdminId;
    tm borrowTime;
    tm returnTime;
    bool returned;
public:
    bool operator==(const BorrowList &borrowList)const          //对==进行操作符重载(否则list的remove方法报错）
    {
        if (borrowListId == borrowList.borrowListId) {
            return true;
        } else {
            return false;
        }
    }
    BorrowList(int borrowListId, int borrowerId, int AdminId, long long bookISBN, tm &time, bool returned = false): borrowListId(borrowListId), borrowerId(borrowerId), AdminId(AdminId), bookISBN(bookISBN), borrowTime(time), returnTime(time), returned(returned)
    {
        returnTime.tm_mon++;
    }
    BorrowList() {}
    ~BorrowList() {}
    int get_borrowerId()
    {
        return borrowerId;
    }
    int get_borrowListId()
    {
        return borrowListId;
    }

    long long get_bookISBN()
    {
        return bookISBN;
    }
    int get_adminId()
    {
        return AdminId;
    }
    string get_borrowTime()
    {
        string time = asctime(&borrowTime);
        return time;
    }
    string get_returnTime()
    {
        string time = asctime(&returnTime);
        return time;
    }
    bool IsOverdue()
    {
        time_t timeNow;
        time(&timeNow);
        time_t timeReturn = mktime(&returnTime);
        return timeNow > timeReturn;
    }
    int OverdueTime()
    {
        time_t timeNow;
        time(&timeNow);
        time_t timeReturn = mktime(&returnTime);
        return timeNow - timeReturn;
    }
    bool IsReturned()
    {
        return returned;
    }
};
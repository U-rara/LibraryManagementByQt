#pragma once

#include "BorrowList.h"
#include <fstream>
#include <list>
#include "BookManagement.h"
#include "Book.h"
#include "tm.h"

class BorrowListManagement
{
private:
    list<BorrowList> BorrowListMgm;
    int BorrowListNums;
public:
    BorrowListManagement()
    {
        InputBorrowListsFromFile();
        BorrowListNums=static_cast<int>(BorrowListMgm.size());
    }
    int get_BorrowListNums()
    {
        return BorrowListNums;
    }
    void AddBorrowList(BorrowList &BorrowList)
    {
        BorrowListMgm.push_front(BorrowList);
        BorrowListNums++;
    }
    void DeleteBorrowList(BorrowList &BorrowList)
    {
        BorrowListMgm.remove(BorrowList);
        BorrowListNums--;
    }
    void ModifyBorrowList(BorrowList &oldBorrowList, BorrowList &newBorrowList)
    {
        DeleteBorrowList(oldBorrowList);
        AddBorrowList(newBorrowList);
    }
   bool FindBorrowList(int id,BorrowList** bl)
    {
        for (list<BorrowList>::iterator it = BorrowListMgm.begin(); it != BorrowListMgm.end(); it++) {
            if (it->get_borrowListId() == id) {
                *bl = &(*it);
                return true;
            }
        }
        return false;
    }
    BorrowList& get_BorrowList_ByIndex(int i)
    {
        list<BorrowList>::iterator it=BorrowListMgm.begin();
        while(i--){
            it++;
        }
        return *it;
    }
    void PullBorrowRequest(long long ISBN,int borrowerId)
    {
        time_t timeNow;
        time(&timeNow);
        tm time=*(localtime(&timeNow));
        BorrowList newBl(BorrowListNums+100001,borrowerId,ISBN,time);
        AddBorrowList(newBl);
    }
    bool OutputBorrowListsToFile()
    {
        QFile file("borrowlist_data.txt");
        file.open(QIODevice::WriteOnly);        //使用writeonly访问清空文件
        file.close();
        if (file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream.seek(file.size());
            stream.setCodec("utf-8");
            list<BorrowList>::iterator it;
            for (it = BorrowListMgm.begin(); it != BorrowListMgm.end(); it++) {
                stream << it->get_borrowListId() << "\t";
                stream << it->get_borrowerId() << "\t";
                stream << it->get_bookISBN() << "\t";
                stream << it->get_adminId() << "\t";
                stream << it->IsReturned() << "\t";
                stream << QString::fromStdString(it->get_borrowTime());
            }
            file.close();
            return true;
        }
    }
    bool InputBorrowListsFromFile()
    {
        BorrowListNums=0;
        BorrowListMgm.clear();
        QFile file("borrowlist_data.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while (!file.atEnd())
            {
                QByteArray line = file.readLine();
                QString data(line);
                QString temp[20];
                int j = 0;
                for (int i = 0; data[i] != '\0'; i++) {
                    if (data[i] != '\t') {
                        temp[j] += data[i];
                    } else {
                        j++;
                        continue;
                    }
                }
                tm time;
                strptime(temp[5].toStdString().c_str(), "%a %b %d %H:%M:%S %Y", &time); //Windows的time标准库中没有该函数 tm.h 中重写（来自Linux gcc标准库）
                BorrowList newBorrowList(temp[0].toInt(), temp[1].toInt(),temp[2].toLongLong(),time,temp[3].toInt(),temp[4].toInt());
                AddBorrowList(newBorrowList);
            }
            file.close();
        }
        return true;
    }
};

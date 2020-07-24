#pragma once

#include "ReturnList.h"
#include "BorrowListManagement.h"
#include "tm.h"
class ReturnListManagement:public BorrowListManagement
{
private:
    list<ReturnList> ReturnListMgm;
    int ReturnListNums;
public:
    ReturnListManagement(){
        InputReturnListsFromFile();
        ReturnListNums=static_cast<int>(ReturnListMgm.size());
    }
    int get_ReturnListNums(){
        return ReturnListNums;
    }
    void AddReturnList(ReturnList &returnList){
        ReturnListMgm.push_front(returnList);
        ReturnListNums++;
    }
    bool FindReturnList(int id,ReturnList** bl)
    {
        for (list<ReturnList>::iterator it = ReturnListMgm.begin(); it != ReturnListMgm.end(); it++) {
            if (it->get_returnListId() == id) {
                *bl = &(*it);
                return true;
            }
        }
        return false;
    }
    ReturnList& get_ReturnList_ByIndex(int i){
        list<ReturnList>::iterator it=ReturnListMgm.begin();
        while(i--){
            it++;
        }
        return *it;
    }
    void DeleteReturnList(ReturnList &returnList)
    {
        ReturnListMgm.remove(returnList);
        ReturnListNums--;
    }
    bool PullReturnRequest(int borrowListId)
    {
        bool flag;
        BorrowList *bl;
        flag = FindBorrowList(borrowListId,&bl);
        if(!flag){
            return false;
        }
        time_t timeNow;
        time(&timeNow);
        tm time=*(localtime(&timeNow));
        ReturnList newRl(ReturnListNums+100001,*bl,time);
        AddReturnList(newRl);
        return true;
    }
    bool OutputReturnListsToFile()
    {
        QFile file("returnlist_data.txt");
        file.open(QIODevice::WriteOnly);        //使用writeonly访问清空文件
        file.close();
        if (file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream.seek(file.size());
            stream.setCodec("utf-8");
            list<ReturnList>::iterator it;
            for (it = ReturnListMgm.begin(); it != ReturnListMgm.end(); it++) {
                stream << it->get_returnListId() <<"\t";
                stream << it->get_borrowListId() << "\t";
                stream << it->get_adminId() <<"\t";
                stream << it->get_borrowerId() << "\t";
                stream << it->IsOverdue() << "\t";
                stream << QString::fromStdString(it->get_returnedTime());
            }
            file.close();
            return true;
        }
        return false;
    }
    bool InputReturnListsFromFile()
    {
        ReturnListNums=0;
        ReturnListMgm.clear();
        QFile file("returnlist_data.txt");
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
                int id=temp[1].toInt();
                BorrowList *bl;
                BorrowListManagement::FindBorrowList(id,&bl);
                ReturnList newReturnList(temp[0].toInt(),*bl,time,temp[2].toInt());
                AddReturnList(newReturnList);
            }
            file.close();
            return true;
        }else{
            return false;
        }
    }
};

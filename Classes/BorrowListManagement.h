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
    BorrowListManagement(): BorrowListNums(0) {}
    int get_BorrowListNums()
    {
        return BorrowListNums;
    }
    void AddBorrowList(BorrowList &BorrowList)
    {
        BorrowListMgm.push_back(BorrowList);
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
    BorrowList &FindBorrowList(int id)
    {
        for (list<BorrowList>::iterator it = BorrowListMgm.begin(); it != BorrowListMgm.end(); it++) {
            if (it->get_borrowListId() == id) {
                return *it;
            }
        }
        throw "BorrowList Not Found";
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
                stream << it->get_adminId() << "\t";
                stream << it->get_bookISBN() << "\t";
                stream << it->IsReturned() << "\t";
                stream << QString::fromStdString(it->get_borrowTime())<<"\t";
                stream <<endl;
            }
            file.close();
            return true;
        }
    }
    bool InputBorrowListsFromFile()
    {
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
                BorrowList newBorrowList(temp[0].toInt(), temp[1].toInt(),temp[2].toInt(), temp[3].toLongLong(), time, temp[4].toInt());
                //              BorrowListMgm.push_back(newBorrowList);
            }
            file.close();
        }
        //        char data[1024];
        //        ifstream infile;
        //        infile.open(":/data/Classes/Data/borrowlist_data.txt");
        //        while (!infile.eof()) {
        //            infile.getline(data, 200);
        //            string temp[20];
        //            int j = 0;
        //            for (int i = 0; data[i] != '\0'; i++) {
        //                if (data[i] != '\t') {
        //                    temp[j] += data[i];
        //                } else {
        //                    j++;
        //                    continue;
        //                }
        //            }

        //        }
        //        infile.close();
        //BorrowListMgm.pop_back(); //删除最后一个空节点
        return true;
    }
};

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
        ofstream outfile;
        outfile.open("./BorrowList/data.txt");
        list<BorrowList>::iterator it;
        for (it = BorrowListMgm.begin(); it != BorrowListMgm.end(); it++) {
            outfile << it->get_borrowListId() << "\t";
            outfile << it->get_borrowerId() << "\t";
            outfile << it->get_adminId() << "\t";
            outfile << it->get_bookISBN() << "\t";
            outfile << it->IsReturned() << "\t";
            outfile << it->get_borrowTime();
        }
        outfile.close();
        return true;
    }
    bool InputBorrowListsFromFile()
    {
        char data[1024];
        ifstream infile;
        infile.open("./BorrowList/data.txt");
        while (!infile.eof()) {
            infile.getline(data, 200);
            string temp[20];
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
            strptime(temp[5].c_str(), "%a %b %d %H:%M:%S %Y", &time); //Windows无法使用 tm.h 中重写
            BorrowList newBorrowList(atoi(temp[0].c_str()), atoi(temp[1].c_str()), atoi(temp[2].c_str()), atoll(temp[3].c_str()), time, atoi(temp[4].c_str()));
            BorrowListMgm.push_back(newBorrowList);
        }
        infile.close();
        BorrowListMgm.pop_back(); //删除最后一个空节点
        return true;
    }
};
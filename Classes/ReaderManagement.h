#pragma once

#include "Reader.h"
#include <list>
#include <fstream>
using namespace std;

class ReaderManagement
{
private:
    list<Reader> ReaderMgm;
    int ReaderNums;
public:
    ReaderManagement() {
        InputReadersFromFile();
        ReaderNums=ReaderMgm.size();
    }
    int get_ReaderNums()
    {
        return ReaderNums;
    }
    void AddReader(Reader &reader)
    {
        ReaderMgm.push_back(reader);
        ReaderNums++;
    }
    void DeleteReader(Reader &reader)
    {
        ReaderMgm.remove(reader);
        ReaderNums--;
    }
    void ModifyReader(Reader &oldReader, Reader &newReader)
    {
        DeleteReader(oldReader);
        AddReader(newReader);
    }
    bool LoginReader(int acc,string pas){
        Reader readerToLogin;
        FindReader(acc,readerToLogin);
        return readerToLogin.Check(pas);
    }
    bool FindReader(int account,Reader& ret){
        for (list<Reader>::iterator it = ReaderMgm.begin(); it != ReaderMgm.end(); it++) {
            if (it->get_account() == account) {
                ret= *it;
                return true;
            }
        }
        return false;
    }
    bool OutputReadersToFile()
    {
        ofstream outfile;
        outfile.open("C:\\Users\\wuwei\\Desktop\\QT\\Library\\Classes\\Reader\\data.txt");
        list<Reader>::iterator it;
        for (it = ReaderMgm.begin(); it != ReaderMgm.end(); it++) {
            outfile << it->get_id() << "\t";
            outfile << it->get_account() << "\t";
            outfile << it->get_name() << "\t";
            outfile << it->get_password() << "\t";
            outfile << it->get_totalBorrowedBooks() << "\t";
            outfile << it->get_curBorrowedBooks() << "\t";
            outfile << endl;
        }
        outfile.close();
        return true;
    }
    bool InputReadersFromFile()
    {
        char data[1024];
        ifstream infile;
        infile.open("C:\\Users\\wuwei\\Desktop\\QT\\Library\\Classes\\Reader\\data.txt");
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
            // infile.close();
            Reader newReader(atoll(temp[0].c_str()), atoi(temp[1].c_str()), temp[2], temp[3],atoi(temp[4].c_str()), atoi(temp[5].c_str()));
            AddReader(newReader);
        }
        infile.close();
        ReaderMgm.pop_back(); //删除最后一个空节点
        return true;
    }
};

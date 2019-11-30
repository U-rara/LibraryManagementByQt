#pragma once

#include "Reader.h"
#include <list>
#include <fstream>
#include "QFile"
#include "QTextStream"
using namespace std;

class ReaderManagement
{
private:
    list<Reader> ReaderMgm;
    int ReaderNums;
public:
    ReaderManagement() {
        InputReadersFromFile();
        ReaderNums=static_cast<int>(ReaderMgm.size());
    }
    int get_ReaderNums()
    {
        return ReaderNums;
    }
    void AddReader(Reader &reader)
    {
        ReaderMgm.push_front(reader);
        ReaderNums++;
    }
    void DeleteReader(Reader &reader)
    {
        ReaderMgm.remove(reader);
        ReaderNums--;
    }
    void DeleteReader(long long account)
    {
        Reader reader;
        FindReader(account,reader);
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
    bool FindReader(long long account,Reader& ret){
        for (list<Reader>::iterator it = ReaderMgm.begin(); it != ReaderMgm.end(); it++) {
            if (it->get_account() == account) {
                ret= *it;
                return true;
            }
        }
        return false;
    }
    Reader& get_Reader_ByIndex(int i)
    {
        list<Reader>::iterator it=ReaderMgm.begin();
        while(i--){
            it++;
        }
        return *it;
    }
    bool OutputReadersToFile()
    {
        QFile file("reader_data.txt");
        file.open(QIODevice::WriteOnly);        //使用writeonly访问清空文件
        file.close();
        if (file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream.seek(file.size());
            stream.setCodec("utf-8");
            list<Reader>::iterator it;
            for (it = ReaderMgm.begin(); it != ReaderMgm.end(); it++) {
                stream << it->get_id() << "\t";
                stream << it->get_account() << "\t";
                stream << QString::fromStdString(it->get_name()) << "\t";
                stream << QString::fromStdString(it->get_password()) << "\t";
                stream << it->get_totalBorrowedBooks() << "\t";
                stream << it->get_curBorrowedBooks() << "\t";
                stream << endl;
            }
            file.close();
            return true;
        }
    }
    bool InputReadersFromFile()
    {
        QFile file("reader_data.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while (!file.atEnd())
            {
                QByteArray line = file.readLine();
                QString str(line);
                string data=str.toStdString();
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
                Reader newReader(atoll(temp[0].c_str()), atoi(temp[1].c_str()), temp[2], temp[3],atoi(temp[4].c_str()), atoi(temp[5].c_str()));
                AddReader(newReader);
            }
            file.close();
            //        char data[1024];
            //        ifstream infile;
            //        infile.open(":/data/Classes/Data/reader_data.txt");
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
            //            // infile.close();

        }
        //ReaderMgm.pop_back(); //删除最后一个空节点
        return true;
    }
};

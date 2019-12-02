#pragma once

#include <fstream>
#include "Book.h"
#include <list>
#include "QFile"
#include "QTextStream"

using namespace std;

class BookManagement
{
    list<Book> BookMgm;
    int BookNums;
public:
    BookManagement() {
        InputBooksFromFile();
        BookNums=static_cast<int>(BookMgm.size());
    }
    int get_BookNums(){
        return BookNums;
    }
    void AddBook(Book &book)
    {
        BookMgm.push_front(book);
        BookNums ++;
    }
    void DeletBook(Book &book)
    {
        BookMgm.remove(book);
        BookNums --;
    }
    void DeletBook(long long ISBN)
    {
        Book temp;
        FindBook(ISBN,temp);
        BookMgm.remove(temp);
        BookNums --;
    }
    void ModifyBook(Book &oldBook, Book &newBook)
    {
        DeletBook(oldBook);
        AddBook(newBook);
    }
    bool FindBook(long long ISBN,Book& ret)
    {
        for (list<Book>::iterator it = BookMgm.begin(); it != BookMgm.end(); it++) {
            if (it->get_ISBN() == ISBN) {
                ret= *it;
                return true;
            }
        }
        return false;
    }
    bool FindBook(long long ISBN,Book** ret)
    {
        for (list<Book>::iterator it = BookMgm.begin(); it != BookMgm.end(); it++) {
            if (it->get_ISBN() == ISBN) {
                *ret=&(*it);
                return true;
            }
        }
        return false;
    }
    Book& get_Book_ByIndex(int i){
        list<Book>::iterator it=BookMgm.begin();
        while(i--){
            it++;
        }
        return *it;
    }
    bool OutputBooksToFile()
    {
        QFile file("book_data.txt");
        file.open(QIODevice::WriteOnly);        //使用writeonly访问清空文件
        file.close();
        if (file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream.seek(file.size());
            stream.setCodec("utf-8");
            list<Book>::iterator it;
            for (it = BookMgm.begin(); it != BookMgm.end(); it++) {
                stream << QString::fromStdString(it->get_bookName()) << "\t";
                stream << QString::fromStdString(it->get_author()) << "\t";
                stream << QString::fromStdString(it->get_publisher()) << "\t";
                stream << it->get_ISBN() << "\t";
                stream << QString::fromStdString(it->get_loc()) << "\t";
                stream << QString::fromStdString(it->get_findMark()) << "\t";
                stream << it->get_curNums() << "\t";
                stream << it->get_totalNums() << "\t";
                stream << it->get_borrowedTimes() << "\t";
                stream << endl;
            }
            file.close();
        }
        //        ofstream outfile;
        //        outfile.open(":/data/Classes/Data/book_data.txt");

        //        outfile.close();
        return true;
    }

    bool InputBooksFromFile()
    {
        BookNums=0;
        BookMgm.clear();
        QFile file("book_data.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while (!file.atEnd())
            {
                QByteArray line = file.readLine();
                QString data(line);
                //              string data=str.toStdString();
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
                Book newbook(temp[0].toStdString(), temp[1].toStdString(), temp[2].toStdString(), temp[3].toLongLong(), temp[4].toStdString(), temp[5].toStdString(),temp[6].toInt(),temp[7].toInt(),temp[8].toInt());
                AddBook(newbook);
            }
            file.close();
        }
        //        char data[1024];
        //        ifstream infile;
        //        infile.open(":/data/Classes/Data/book_data.txt");
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
        //BookMgm.pop_front();
        return true;
    }
};

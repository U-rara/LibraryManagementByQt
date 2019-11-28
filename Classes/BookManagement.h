#pragma once

#include <fstream>
#include "Book.h"
#include <list>

using namespace std;

class BookManagement
{
    list<Book> BookMgm;
    int BookNums;
public:
    BookManagement() {
        InputBooksFromFile();
        BookNums=BookMgm.size();
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
        BookNums -= book.get_totalNums();
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
    Book& get_Book_ByIndex(int i){
        list<Book>::iterator it=BookMgm.begin();
        while(i--){
            it++;
        }
        return *it;
    }
    bool OutputBooksToFile()
    {
        ofstream outfile;
        outfile.open("C:\\Users\\wuwei\\Desktop\\QT\\Library\\Classes\\Book\\data.txt");
        list<Book>::iterator it;
        for (it = BookMgm.begin(); it != BookMgm.end(); it++) {
            outfile << it->get_bookName() << "\t";
            outfile << it->get_author() << "\t";
            outfile << it->get_publisher() << "\t";
            outfile << it->get_ISBN() << "\t";
            outfile << it->get_loc() << "\t";
            outfile << it->get_findMark() << "\t";
            outfile << it->get_curNums() << "\t";
            outfile << it->get_totalNums() << "\t";
            outfile << it->get_borrowedTimes() << "\t";
            outfile << endl;
        }
        outfile.close();
        return true;
    }

    bool InputBooksFromFile()
    {
        char data[1024];
        ifstream infile;
        infile.open("C:\\Users\\wuwei\\Desktop\\QT\\Library\\Classes\\Book\\data.txt");
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
            Book newbook(temp[0], temp[1], temp[2], atoll(temp[3].c_str()), temp[4], temp[5], atoi(temp[6].c_str()),atoi(temp[7].c_str()),atoi(temp[8].c_str()));
            AddBook(newbook);
            BookNums+=atoi(temp[7].c_str());
        }
        infile.close();
        BookMgm.pop_front();
        return true;
    }
};

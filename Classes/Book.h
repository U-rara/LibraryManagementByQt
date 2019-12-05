#pragma once

#include <iostream>

using namespace std;
class Book
{
private:
    string bookName;    //书名
    string publisher;   //出版社
    string author;      //作者
    long long ISBN;     //国际标准书号(作为书类对象的唯一标识)
    string findMark;    //索书号
    string loc;         //馆藏地点
    int curNums;        //当前馆藏数量
    int totalNums;      //总馆藏数量
    int borrowedTimes;  //被借阅次数
public:
    Book() {}
    Book(string bookName, string author, string publisher, long long ISBN, string loc, string findMark, int curNums,int totalNums,int borrowedTimes) : bookName(bookName), publisher(publisher), author(author), ISBN(ISBN) , findMark(findMark) , loc(loc) , curNums(curNums), totalNums(totalNums) , borrowedTimes(borrowedTimes){}
    ~Book() {}
    bool operator==(const Book &book)const          //对==进行操作符重载(否则list的remove方法报错)，用ISBN进行书籍种类比较
    {
        if (ISBN == book.ISBN) {
            return true;
        } else {
            return false;
        }
    }
    string &get_bookName()  //返回书名
    {
        return bookName;
    }
    string &get_author()    //返回作者名
    {
        return author;
    }
    string &get_publisher()     //返回出版社
    {
        return publisher;
    }
    string &get_loc()       //返回馆藏位置
    {
        return loc;
    }
    string &get_findMark()      //返回索书号
    {
        return findMark;
    }
    int &get_borrowedTimes()    //返回被借阅次数
    {
        return borrowedTimes;
    }
    int &get_curNums()      //返回当前馆藏数量
    {
        return curNums;
    }
    int &get_totalNums()        //返回总馆藏数量
    {
        return totalNums;
    }
    long long &get_ISBN()       //返回ISBN
    {
        return ISBN;
    }
    void BorrowPermitted()
    {
        curNums--;
        borrowedTimes++;
    }
    void ReturnPermitted()
    {
        curNums++;
    }
};


#include "borrowbook.h"
#include "ui_borrowbook.h"
#include "QAbstractItemView"
#include "QPropertyAnimation"
#include "QMessageBox"

BorrowBook::BorrowBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BorrowBook)
{
    ui->setupUi(this);
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(0.91);
    animation->start();


    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->tableWidget->verticalHeader()->setVisible(false); //设置行号不可见
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表宽度自适应
    ui->tableWidget->setFrameShape(QFrame::NoFrame);//设置无边框
    ui->tableWidget->setShowGrid(false); //设置不显示格子线
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选取

    int bookNums=this->bkm.get_BookNums();
    for(int i=0;i<bookNums;i++){
        Book t=this->bkm.get_Book_ByIndex(i);
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::fromStdString(t.get_bookName())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_publisher())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::fromStdString(t.get_author())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t.get_ISBN())));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::fromStdString(t.get_findMark())));
        ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t.get_loc())));
        ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::number(t.get_curNums())));
        ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(QString::number(t.get_totalNums())));
        ui->tableWidget->setItem(rowcount,8,new QTableWidgetItem(QString::number(t.get_borrowedTimes())));
    }
}

void BorrowBook::set_loger(Reader rd)
{
    loger=rd;
}

BorrowBook::~BorrowBook()
{
    delete ui;
}

void BorrowBook::on_button_req_clicked()
{
    if(loger.BorrrowAvailable()){
        QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
        int cnt=0;
        int count=ranges.count();
        for(int i=0;i<count;i++)
        {
            int topRow=ranges.at(i).topRow();
            int bottomRow=ranges.at(i).bottomRow();
            for(int j=topRow;j<=bottomRow;j++)
            {
                cnt++;
            }
            if(cnt>1){
                QMessageBox::critical(this,"错误","只能对单一图书进行借阅申请","确认");
            }else{
                int i = ui->tableWidget->currentRow();
                int num=ui->tableWidget->item(i,6)->text().toInt();
                if(num==0){
                    QMessageBox::critical(this,"错误","该书已全部借出","确认");
                }else{
                    long long ISBN = ui->tableWidget->item(i,3)->text().toLongLong();
                    blm.PullBorrowRequest(ISBN,loger.get_id());
                    blm.OutputBorrowListsToFile();
                    QMessageBox::information(this,"成功","申请成功");
                }
            }
        }
    }else{
        QMessageBox::critical(this,"错误","当前借阅数已超过上限","确认");
    }
}

void BorrowBook::on_button_search_clicked()
{
    QString rule=ui->searchbox->currentText();
    QString data=ui->searchle->text();
    list<Book> found;
    if(rule=="按ISBN"){
        long long ISBN=data.toLongLong();
        Book t;
        bkm.FindBook(ISBN,t);
        ui->tableWidget->setRowCount(0);  //清空列表
        int rowcount=0;
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::fromStdString(t.get_bookName())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_publisher())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::fromStdString(t.get_author())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t.get_ISBN())));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::fromStdString(t.get_findMark())));
        ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t.get_loc())));
        ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::number(t.get_curNums())));
        ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(QString::number(t.get_totalNums())));
        ui->tableWidget->setItem(rowcount,8,new QTableWidgetItem(QString::number(t.get_borrowedTimes())));
    }
    else if(rule=="按作者")
    {
        list<Book> found;
        int count=ui->tableWidget->rowCount();
        for(int i=0;i<count;i++){
            if(ui->tableWidget->item(i,2)->text().toStdString()==data.toStdString()){
                long long ISBN=ui->tableWidget->item(i,3)->text().toLongLong();
                Book t;
                bkm.FindBook(ISBN,t);
                found.push_back(t);
            }
        }
        ui->tableWidget->setRowCount(0);  //清空列表
        list<Book>::iterator t=found.begin();
        for(int i=0;i<static_cast<int>(found.size());i++){
            int rowcount=0;
            ui->tableWidget->insertRow(rowcount);
            ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::fromStdString(t->get_bookName())));
            ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t->get_publisher())));
            ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::fromStdString(t->get_author())));
            ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t->get_ISBN())));
            ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::fromStdString(t->get_findMark())));
            ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t->get_loc())));
            ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::number(t->get_curNums())));
            ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(QString::number(t->get_totalNums())));
            ui->tableWidget->setItem(rowcount,8,new QTableWidgetItem(QString::number(t->get_borrowedTimes())));
            t++;
        }
    }else if(rule=="按书名"){
        list<Book> found;
        int count=ui->tableWidget->rowCount();
        for(int i=0;i<count;i++){
            if(ui->tableWidget->item(i,0)->text().toStdString()==data.toStdString()){
                long long ISBN=ui->tableWidget->item(i,3)->text().toLongLong();
                Book t;
                bkm.FindBook(ISBN,t);
                found.push_back(t);
            }
        }
        list<Book>::iterator t=found.begin();
        ui->tableWidget->setRowCount(0);  //清空列表
        for(int i=0;i<static_cast<int>(found.size());i++){
            int rowcount=0;
            ui->tableWidget->insertRow(rowcount);
            ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::fromStdString(t->get_bookName())));
            ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t->get_publisher())));
            ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::fromStdString(t->get_author())));
            ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t->get_ISBN())));
            ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::fromStdString(t->get_findMark())));
            ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t->get_loc())));
            ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::number(t->get_curNums())));
            ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(QString::number(t->get_totalNums())));
            ui->tableWidget->setItem(rowcount,8,new QTableWidgetItem(QString::number(t->get_borrowedTimes())));
            t++;
        }
     }else if(rule=="按出版社"){
        list<Book> found;
        int count=ui->tableWidget->rowCount();
        for(int i=0;i<count;i++){
            if(ui->tableWidget->item(i,1)->text().toStdString()==data.toStdString()){
                long long ISBN=ui->tableWidget->item(i,3)->text().toLongLong();
                Book t;
                bkm.FindBook(ISBN,t);
                found.push_back(t);
            }
        }
        ui->tableWidget->setRowCount(0);  //清空列表
        list<Book>::iterator t=found.begin();
        for(int i=0;i<static_cast<int>(found.size());i++){
            int rowcount=0;
            ui->tableWidget->insertRow(rowcount);
            ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::fromStdString(t->get_bookName())));
            ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t->get_publisher())));
            ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::fromStdString(t->get_author())));
            ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t->get_ISBN())));
            ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::fromStdString(t->get_findMark())));
            ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t->get_loc())));
            ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::number(t->get_curNums())));
            ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(QString::number(t->get_totalNums())));
            ui->tableWidget->setItem(rowcount,8,new QTableWidgetItem(QString::number(t->get_borrowedTimes())));
            t++;
        }
    }else if(rule=="按索书号"){
        list<Book> found;
        int count=ui->tableWidget->rowCount();
        for(int i=0;i<count;i++){
            if(ui->tableWidget->item(i,4)->text().toStdString()==data.toStdString()){
                long long ISBN=ui->tableWidget->item(i,3)->text().toLongLong();
                Book t;
                bkm.FindBook(ISBN,t);
                found.push_back(t);
            }
        }
        list<Book>::iterator t=found.begin();
        ui->tableWidget->setRowCount(0);  //清空列表
        for(int i=0;i<static_cast<int>(found.size());i++){
            int rowcount=0;
            ui->tableWidget->insertRow(rowcount);
            ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::fromStdString(t->get_bookName())));
            ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t->get_publisher())));
            ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::fromStdString(t->get_author())));
            ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t->get_ISBN())));
            ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::fromStdString(t->get_findMark())));
            ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t->get_loc())));
            ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::number(t->get_curNums())));
            ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(QString::number(t->get_totalNums())));
            ui->tableWidget->setItem(rowcount,8,new QTableWidgetItem(QString::number(t->get_borrowedTimes())));
            t++;
        }
    }else if(rule=="按馆藏地点"){
        list<Book> found;
        int count=ui->tableWidget->rowCount();
        for(int i=0;i<count;i++){
            if(ui->tableWidget->item(i,5)->text().toStdString()==data.toStdString()){
                long long ISBN=ui->tableWidget->item(i,3)->text().toLongLong();
                Book t;
                bkm.FindBook(ISBN,t);
                found.push_back(t);
            }
        }
        list<Book>::iterator t=found.begin();
        ui->tableWidget->setRowCount(0);  //清空列表
        for(int i=0;i<static_cast<int>(found.size());i++){
            int rowcount=0;
            ui->tableWidget->insertRow(rowcount);
            ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::fromStdString(t->get_bookName())));
            ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t->get_publisher())));
            ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::fromStdString(t->get_author())));
            ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t->get_ISBN())));
            ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::fromStdString(t->get_findMark())));
            ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t->get_loc())));
            ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::number(t->get_curNums())));
            ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(QString::number(t->get_totalNums())));
            ui->tableWidget->setItem(rowcount,8,new QTableWidgetItem(QString::number(t->get_borrowedTimes())));
            t++;
        }
    }
}

void BorrowBook::on_button_all_clicked()
{
    bkm.InputBooksFromFile();
    int bookNums=this->bkm.get_BookNums();
    ui->tableWidget->setRowCount(0);  //清空列表
    for(int i=0;i<bookNums;i++){
        Book t=this->bkm.get_Book_ByIndex(i);
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::fromStdString(t.get_bookName())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_publisher())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::fromStdString(t.get_author())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(QString::number(t.get_ISBN())));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::fromStdString(t.get_findMark())));
        ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t.get_loc())));
        ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::number(t.get_curNums())));
        ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(QString::number(t.get_totalNums())));
        ui->tableWidget->setItem(rowcount,8,new QTableWidgetItem(QString::number(t.get_borrowedTimes())));
    }
}

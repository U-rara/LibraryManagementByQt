#include "borrowhistory.h"
#include "ui_borrowhistory.h"
#include "QAbstractItemView"
#include "QPropertyAnimation"
#include "QMessageBox"

BorrowHistory::BorrowHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BorrowHistory)
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
    ui->tableWidget->setRowCount(0);  //清空列表
}

BorrowHistory::~BorrowHistory()
{
    delete ui;
}

void BorrowHistory::set_loger(Reader rd){
    mb.clear();
    loger=rd;
    int BorrowListNums=this->blm.get_BorrowListNums();
    for(int i=0;i<BorrowListNums;i++){
        BorrowList t=this->blm.get_BorrowList_ByIndex(i);
        if(t.get_borrowerId()==loger.get_id()){
            mb.push_front(t);
        }
    }
    this->ui->tableWidget->setRowCount(0);  //清空列表
    list<BorrowList>::iterator t=mb.begin();
    for(int i=0;i<static_cast<int>(mb.size());i++){
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t->get_borrowListId())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::number(t->get_borrowerId())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t->get_bookISBN())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(t->IsPermitted()?"已许可":"未许可"));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t->get_adminId())));
        ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t->get_borrowTime())));
        ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::fromStdString(t->get_returnTime())));
        ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(t->IsReturned()?"已归还":"未归还"));
        t++;
    }
}

void BorrowHistory::on_button_todo_clicked()
{
    list<BorrowList> found;
    int count=ui->tableWidget->rowCount();
    for(int i=0;i<count;i++){
        if(ui->tableWidget->item(i,3)->text()=="未许可"){
            int id=ui->tableWidget->item(i,0)->text().toInt();
            BorrowList *t;
            blm.FindBorrowList(id,&t);
            found.push_back(*t);
        }
    }
    ui->tableWidget->setRowCount(0);  //清空列表
    list<BorrowList>::iterator t=found.begin();
    for(int i=0;i<static_cast<int>(found.size());i++){
        int rowcount=0;
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t->get_borrowListId())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::number(t->get_borrowerId())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t->get_bookISBN())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(t->IsPermitted()?"已许可":"未许可"));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t->get_adminId())));
        ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t->get_borrowTime())));
        ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::fromStdString(t->get_returnTime())));
        ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(t->IsReturned()?"已归还":"未归还"));
        t++;
    }
}

void BorrowHistory::on_button_ok_clicked()
{
    list<BorrowList> found;
    int count=ui->tableWidget->rowCount();
    for(int i=0;i<count;i++){
        if(ui->tableWidget->item(i,7)->text()=="已归还"){
            int id=ui->tableWidget->item(i,0)->text().toInt();
            BorrowList *t;
            blm.FindBorrowList(id,&t);
            found.push_back(*t);
        }
    }
    ui->tableWidget->setRowCount(0);  //清空列表
    list<BorrowList>::iterator t=found.begin();
    for(int i=0;i<static_cast<int>(found.size());i++){
        int rowcount=0;
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t->get_borrowListId())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::number(t->get_borrowerId())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t->get_bookISBN())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(t->IsPermitted()?"已许可":"未许可"));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t->get_adminId())));
        ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t->get_borrowTime())));
        ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::fromStdString(t->get_returnTime())));
        ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(t->IsReturned()?"已归还":"未归还"));
        t++;
    }
}

void BorrowHistory::on_button_no_clicked()
{
    list<BorrowList> found;
    int count=ui->tableWidget->rowCount();
    for(int i=0;i<count;i++){
        if(ui->tableWidget->item(i,7)->text()=="未归还"){
            int id=ui->tableWidget->item(i,0)->text().toInt();
            BorrowList *t;
            blm.FindBorrowList(id,&t);
            found.push_back(*t);
        }
    }
    ui->tableWidget->setRowCount(0);  //清空列表
    list<BorrowList>::iterator t=found.begin();
    for(int i=0;i<static_cast<int>(found.size());i++){
        int rowcount=0;
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t->get_borrowListId())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::number(t->get_borrowerId())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t->get_bookISBN())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(t->IsPermitted()?"已许可":"未许可"));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t->get_adminId())));
        ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t->get_borrowTime())));
        ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::fromStdString(t->get_returnTime())));
        ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(t->IsReturned()?"已归还":"未归还"));
        t++;
    }
}

void BorrowHistory::on_button_searchid_clicked()
{
    QString data=ui->searchle->text();
    int id=data.toInt();
    BorrowList *t;
    blm.FindBorrowList(id,&t);
    ui->tableWidget->setRowCount(0);  //清空列表
    int rowcount=0;
    ui->tableWidget->insertRow(rowcount);
    ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t->get_borrowListId())));
    ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::number(t->get_borrowerId())));
    ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t->get_bookISBN())));
    ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(t->IsPermitted()?"已许可":"未许可"));
    ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t->get_adminId())));
    ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t->get_borrowTime())));
    ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::fromStdString(t->get_returnTime())));
    ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(t->IsReturned()?"已归还":"未归还"));
}

void BorrowHistory::on_button_all_clicked()
{
    ui->tableWidget->setRowCount(0);  //清空列表
    list<BorrowList>::iterator t=mb.begin();
    for(int i=0;i<static_cast<int>(mb.size());i++){
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t->get_borrowListId())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::number(t->get_borrowerId())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t->get_bookISBN())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(t->IsPermitted()?"已许可":"未许可"));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t->get_adminId())));
        ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t->get_borrowTime())));
        ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::fromStdString(t->get_returnTime())));
        ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(t->IsReturned()?"已归还":"未归还"));
        t++;
    }
}

#include "borrowlistm.h"
#include "ui_borrowlistm.h"
#include "QAbstractItemView"
#include "QPropertyAnimation"
#include "QMessageBox"

BorrowListM::BorrowListM(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BorrowListM)
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

    int BorrowListNums=this->blm.get_BorrowListNums();
    for(int i=0;i<BorrowListNums;i++){
        BorrowList t=this->blm.get_BorrowList_ByIndex(i);
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_borrowListId())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::number(t.get_borrowerId())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_bookISBN())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(t.IsPermitted()?"已许可":"未许可"));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t.get_adminId())));
        ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t.get_borrowTime())));
        ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::fromStdString(t.get_returnTime())));
        ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(t.IsReturned()?"已归还":"未归还"));
    }
}

BorrowListM::~BorrowListM()
{
    delete ui;
}

void BorrowListM::set_loger(Admin ad){
    loger=ad;
}

void BorrowListM::on_button_no_clicked()
{
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
            QMessageBox::critical(this,"错误","只能选中单一申请进行审核","确认");
        }else{
            int i = ui->tableWidget->currentRow();
            int id = ui->tableWidget->item(i,0)->text().toInt();
            BorrowList *t;
            blm.FindBorrowList(id,&t);
            if(t->IsPermitted()){
                QMessageBox::critical(this,"错误","无法拒绝已许可的申请","确认");
            }else{
                blm.DeleteBorrowList(*t);
                blm.OutputBorrowListsToFile();
                ui->tableWidget->setRowCount(0);  //清空列表
                int BorrowListNums=this->blm.get_BorrowListNums();
                for(int i=0;i<BorrowListNums;i++){
                    BorrowList t=this->blm.get_BorrowList_ByIndex(i);
                    int rowcount=ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(rowcount);
                    ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_borrowListId())));
                    ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::number(t.get_borrowerId())));
                    ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_bookISBN())));
                    ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(t.IsPermitted()?"已许可":"未许可"));
                    ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t.get_adminId())));
                    ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t.get_borrowTime())));
                    ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::fromStdString(t.get_returnTime())));
                    ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(t.IsReturned()?"已归还":"未归还"));
                }
            }
        }
    }
}

void BorrowListM::on_button_ok_clicked()
{
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
            QMessageBox::critical(this,"错误","只能选中单一申请进行审核","确认");
        }else{
            int i = ui->tableWidget->currentRow();
            int id = ui->tableWidget->item(i,0)->text().toInt();
            BorrowList *t;
            blm.FindBorrowList(id,&t);
            if(t->IsPermitted()){
                QMessageBox::critical(this,"错误","重复许可","确认");
            }else{
                long long readerAcc=t->get_borrowerId();
                Reader *r;
                rdm.FindReader(readerAcc,&r);
                r->BorrowPermitted();
                rdm.OutputReadersToFile();
                long long ISBN=t->get_bookISBN();
                Book *b;
                bkm.FindBook(ISBN,&b);
                b->BorrowPermitted();
                bkm.OutputBooksToFile();
                t->PermitBorrow(loger.get_id());
                blm.OutputBorrowListsToFile();
                ui->tableWidget->setRowCount(0);  //清空列表
                int BorrowListNums=this->blm.get_BorrowListNums();
                for(int i=0;i<BorrowListNums;i++){
                    BorrowList t=this->blm.get_BorrowList_ByIndex(i);
                    int rowcount=ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(rowcount);
                    ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_borrowListId())));
                    ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::number(t.get_borrowerId())));
                    ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_bookISBN())));
                    ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(t.IsPermitted()?"已许可":"未许可"));
                    ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t.get_adminId())));
                    ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t.get_borrowTime())));
                    ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::fromStdString(t.get_returnTime())));
                    ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(t.IsReturned()?"已归还":"未归还"));
                }
            }
        }
    }
}

void BorrowListM::on_button_todo_clicked()
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

void BorrowListM::on_button_done_clicked()
{
    list<BorrowList> found;
    int count=ui->tableWidget->rowCount();
    for(int i=0;i<count;i++){
        if(ui->tableWidget->item(i,3)->text()=="已许可"){
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

void BorrowListM::on_button_all_clicked()
{
    blm.InputBorrowListsFromFile();
    ui->tableWidget->setRowCount(0);  //清空列表
    int BorrowListNums=this->blm.get_BorrowListNums();
    for(int i=0;i<BorrowListNums;i++){
        BorrowList t=this->blm.get_BorrowList_ByIndex(i);
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_borrowListId())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::number(t.get_borrowerId())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_bookISBN())));
        ui->tableWidget->setItem(rowcount,3,new QTableWidgetItem(t.IsPermitted()?"已许可":"未许可"));
        ui->tableWidget->setItem(rowcount,4,new QTableWidgetItem(QString::number(t.get_adminId())));
        ui->tableWidget->setItem(rowcount,5,new QTableWidgetItem(QString::fromStdString(t.get_borrowTime())));
        ui->tableWidget->setItem(rowcount,6,new QTableWidgetItem(QString::fromStdString(t.get_returnTime())));
        ui->tableWidget->setItem(rowcount,7,new QTableWidgetItem(t.IsReturned()?"已归还":"未归还"));
    }
}

void BorrowListM::on_button_searchid_clicked()
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

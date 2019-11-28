#include "bookm.h"
#include "ui_bookm.h"
#include "QAbstractItemView"
#include "QPropertyAnimation"

BookM::BookM(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookM)
{
    ui->setupUi(this);
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(0.91);
    animation->start();

    ab=new bm_AddBook;
    connect(ab,SIGNAL(sendData(Book)),this,SLOT(receiveData(Book)));

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

    BookM::~BookM()
    {
        delete ui;
    }

void BookM::on_button_add_clicked()
{
    ab->show();
}

void BookM::receiveData(Book newBook){
    bkm.AddBook(newBook);
    bkm.OutputBooksToFile();
    int bookNums=this->bkm.get_BookNums();
    ui->tableWidget->setRowCount(0);
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

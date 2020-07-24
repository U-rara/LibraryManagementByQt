#include "adminm.h"
#include "ui_adminm.h"
#include "QAbstractItemView"
#include "QPropertyAnimation"
#include "QMessageBox"

AdminM::AdminM(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminM)
{
    ui->setupUi(this);
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(0.91);
    animation->start();

    aa=new am_AddAdmin;
    connect(aa,SIGNAL(sendAdmin_aa(Admin)),this,SLOT(receiveAdmin_aa(Admin)));

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->tableWidget->verticalHeader()->setVisible(false); //设置行号不可见
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表宽度自适应
    ui->tableWidget->setFrameShape(QFrame::NoFrame);//设置无边框
    ui->tableWidget->setShowGrid(false); //设置不显示格子线
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选取

    int adminNums=this->adm.get_AdminNums();
    for(int i=0;i<adminNums;i++){
        Admin t=this->adm.get_Admin_ByIndex(i);
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
    }
}

AdminM::~AdminM()
{
    delete ui;
}

void AdminM::on_button_add_clicked()
{
    aa->show();
}

void AdminM::receiveAdmin_aa(Admin newAdmin){
    adm.AddAdmin(newAdmin);
    adm.OutputAdminsToFile();
    int adminNums=this->adm.get_AdminNums();
    ui->tableWidget->setRowCount(0);  //清空列表
    for(int i=0;i<adminNums;i++){
        Admin t=this->adm.get_Admin_ByIndex(i);
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
    }
}

void AdminM::on_button_delete_clicked()
{
    QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
    int count=ranges.count();
    for(int i=0;i<count;i++)
    {
        int topRow=ranges.at(i).topRow();
        int bottomRow=ranges.at(i).bottomRow();
        for(int j=topRow;j<=bottomRow;j++)
        {
            int acc=ui->tableWidget->item(j,2)->text().toInt();
            adm.DeleteAdmin(acc);
        }
        adm.OutputAdminsToFile();
        int adminNums=this->adm.get_AdminNums();
        ui->tableWidget->setRowCount(0);  //清空列表
        for(int i=0;i<adminNums;i++){
            Admin t=this->adm.get_Admin_ByIndex(i);
            int rowcount=ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(rowcount);
            ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
            ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
            ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
        }
    }
}

void AdminM::on_button_setpas_clicked()
{
    QList<QTableWidgetSelectionRange>ranges = ui->tableWidget->selectedRanges();
    int count=ranges.count();
    for(int i=0;i<count;i++)
    {
        int topRow=ranges.at(i).topRow();
        int bottomRow=ranges.at(i).bottomRow();
        for(int j=topRow;j<=bottomRow;j++)
        {
            int account=ui->tableWidget->item(j,2)->text().toInt();
            Admin *t;
            adm.FindAdmin(account,&t);
            t->set_password("123");
        }
        adm.OutputAdminsToFile();
        QMessageBox::information(this,"成功","已重置为初始密码",QMessageBox::Yes);
    }
}

void AdminM::on_button_all_clicked()
{
    adm.InputAdminsFromFile();
    ui->tableWidget->setRowCount(0);  //清空列表
    int adminNums=this->adm.get_AdminNums();
    for(int i=0;i<adminNums;i++){
        Admin t=this->adm.get_Admin_ByIndex(i);
        int rowcount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowcount);
        ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
        ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
        ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
    }
}

void AdminM::on_button_search_clicked()
{
    int acc=ui->searchle->text().toInt();
    Admin t;
    adm.FindAdmin(acc,t);
    int rowcount=0;
    ui->tableWidget->setRowCount(0);  //清空列表
    ui->tableWidget->insertRow(rowcount);
    ui->tableWidget->setItem(rowcount,0,new QTableWidgetItem(QString::number(t.get_id())));
    ui->tableWidget->setItem(rowcount,1,new QTableWidgetItem(QString::fromStdString(t.get_name())));
    ui->tableWidget->setItem(rowcount,2,new QTableWidgetItem(QString::number(t.get_account())));
}


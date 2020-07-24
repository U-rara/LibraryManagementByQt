#include "readerinfo.h"
#include "ui_readerinfo.h"
#include "QMessageBox"

ReaderInfo::ReaderInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderInfo)
{
    ui->setupUi(this);
}

ReaderInfo::~ReaderInfo()
{
    delete ui;
}

void ReaderInfo::set_loger(Reader rd){
    loger=rd;
    ui->label_2->setText(QString::fromStdString(loger.get_name()+"  同学                 学号：")+QString::number(loger.get_id()));
}

void ReaderInfo::on_but_ok_clicked()
{
    if(ui->line_password->text()==""){
        QMessageBox::critical(this,"错误","输入为空，请重新输入","确认");
    }else{
        rdm.ChangePas(loger,ui->line_password->text().toStdString());
        rdm.OutputReadersToFile();
        QMessageBox::information(nullptr, "", "修改成功！");
    }
}

#include "admininfo.h"
#include "ui_admininfo.h"
#include "QMessageBox"

AdminInfo::AdminInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminInfo)
{
    ui->setupUi(this);

}

AdminInfo::~AdminInfo()
{
    delete ui;
}

void AdminInfo::set_loger(Admin ad){
    loger=ad;
    ui->label_2->setText(QString::fromStdString("管理员： "+loger.get_name()+"                 工号：")+QString::number(loger.get_id()));
}

void AdminInfo::on_but_ok_clicked()
{
    if(ui->line_password->text()==""){
        QMessageBox::critical(this,"错误","输入为空，请重新输入","确认");
    }else{
        adm.ChangePas(loger,ui->line_password->text().toStdString());
        adm.OutputAdminsToFile();
        QMessageBox::information(nullptr, "", "修改成功！");
    }
}

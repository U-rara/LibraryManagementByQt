#include "returnbook.h"
#include "ui_returnbook.h"
#include "QPropertyAnimation"
#include "QMessageBox"

ReturnBook::ReturnBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReturnBook)
{
    ui->setupUi(this);
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(0.91);
    animation->start();
}

ReturnBook::~ReturnBook()
{
    delete ui;
}

void ReturnBook::on_but_ok_clicked()
{
    int id=ui->line_bid->text().toInt();
    if(!rlm.PullReturnRequest(id)){
        QMessageBox::critical(this,"错误","查无此号，请核对后重新输入","确认");
    }else{
        rlm.OutputReturnListsToFile();
        QMessageBox::information(this,"成功","申请成功");
    }
}

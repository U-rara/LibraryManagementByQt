#include "am_addadmin.h"
#include "ui_am_addadmin.h"
#include "QPropertyAnimation"
#include "QMouseEvent"

am_AddAdmin::am_AddAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::am_AddAdmin)
{
    ui->setupUi(this);
    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(0.91);
    animation->start();
    this->setWindowFlags(Qt::FramelessWindowHint);
    isMove=false;
}

am_AddAdmin::~am_AddAdmin()
{
    delete ui;
}

void am_AddAdmin::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = true;
        startPoint = event->globalPos();
        windowPoint = this->frameGeometry().topLeft();
    }
}

void am_AddAdmin::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - startPoint;      //移动中的鼠标位置相对于初始位置的相对位置
        this->move(windowPoint + relativePos );                    //移动窗体
    }
}

void am_AddAdmin::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = false;                                     //改变移动状态
    }
}

void am_AddAdmin::on_but_ok_clicked()
{
    QString name=ui->lename->text();
    QString id=ui->leid->text();
    QString account=ui->leacc->text();
    Admin newAdmin(id.toInt(),account.toInt(),name.toStdString());
    emit sendAdmin_aa(newAdmin);
    ui->lename->clear();
    ui->leid->clear();
    ui->leacc->clear();
    this->close();
}

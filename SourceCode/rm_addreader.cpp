#include "rm_addreader.h"
#include "ui_rm_addreader.h"
#include "QPropertyAnimation"
#include "QMouseEvent"

rm_AddReader::rm_AddReader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rm_AddReader)
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

rm_AddReader::~rm_AddReader()
{
    delete ui;
}

void rm_AddReader::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = true;
        startPoint = event->globalPos();
        windowPoint = this->frameGeometry().topLeft();
    }
}

void rm_AddReader::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - startPoint;      //移动中的鼠标位置相对于初始位置的相对位置
        this->move(windowPoint + relativePos );                    //移动窗体
    }
}

void rm_AddReader::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = false;                                     //改变移动状态
    }
}


void rm_AddReader::on_but_ok_clicked()
{
    QString name=ui->lename->text();
    QString id=ui->leid->text();
    QString account=ui->leacc->text();
    Reader newReader(id.toLongLong(),account.toInt(),name.toStdString());
    emit sendReader_ar(newReader);
    ui->lename->clear();
    ui->leid->clear();
    ui->leacc->clear();
    this->close();
}

void rm_AddReader::on_but_no_clicked()
{
    ui->lename->clear();
    ui->leid->clear();
    ui->leacc->clear();
    this->close();
}

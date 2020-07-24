#include "rm_modifyreader.h"
#include "ui_rm_modifyreader.h"
#include "QPropertyAnimation"
#include "QMouseEvent"

rm_ModifyReader::rm_ModifyReader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rm_ModifyReader)
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

rm_ModifyReader::~rm_ModifyReader()
{
    delete ui;
}

void rm_ModifyReader::receiveReader_mr(Reader old){
    oldReader=old;
    ui->leid->setText(QString::number(oldReader.get_id()));
    ui->lename->setText(QString::fromStdString(oldReader.get_name()));
    ui->leacc->setText(QString::number(oldReader.get_account()));
    ui->lecurnum->setText(QString::number(oldReader.get_curBorrowedBooks()));
    ui->letonum->setText(QString::number(oldReader.get_totalBorrowedBooks()));
}

void rm_ModifyReader::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = true;
        startPoint = event->globalPos();
        windowPoint = this->frameGeometry().topLeft();
    }
}

void rm_ModifyReader::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - startPoint;      //移动中的鼠标位置相对于初始位置的相对位置
        this->move(windowPoint + relativePos );                    //移动窗体
    }
}

void rm_ModifyReader::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = false;                                     //改变移动状态
    }
}

void rm_ModifyReader::on_but_ok_clicked()
{
    QString name=ui->lename->text();
    QString id=ui->leid->text();
    QString account=ui->leacc->text();
    QString tonum=ui->letonum->text();
    QString curnum=ui->lecurnum->text();
    Reader newReader(id.toLongLong(),account.toInt(),name.toStdString(),oldReader.get_password(),tonum.toInt(),curnum.toInt());
    emit sendReader_mr(oldReader,newReader);
    ui->lename->clear();
    ui->leid->clear();
    ui->leacc->clear();
    ui->lecurnum->clear();
    ui->letonum->clear();
    this->close();
}

void rm_ModifyReader::on_but_no_clicked()
{
    ui->lename->clear();
    ui->leid->clear();
    ui->leacc->clear();
    ui->lecurnum->clear();
    ui->letonum->clear();
    this->close();
}

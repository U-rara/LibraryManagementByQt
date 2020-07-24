#include "bm_addbook.h"
#include "ui_bm_addbook.h"
#include "QPropertyAnimation"
#include "QMouseEvent"


bm_AddBook::bm_AddBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bm_AddBook)
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

bm_AddBook::~bm_AddBook()
{
    delete ui;
}

void bm_AddBook::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = true;
        startPoint = event->globalPos();
        windowPoint = this->frameGeometry().topLeft();
    }
}

void bm_AddBook::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - startPoint;      //移动中的鼠标位置相对于初始位置的相对位置
        this->move(windowPoint + relativePos );                    //移动窗体
    }
}

void bm_AddBook::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = false;                                     //改变移动状态
    }
}

void bm_AddBook::on_but_ok_clicked()
{
    QString name=ui->etname->text();
    QString publisher=ui->etpublish->text();
    QString author=ui->etauthor->text();
    QString ISBN=ui->etISBN->text();
    QString findMark=ui->etfindmark->text();
    QString loc=ui->etloc->text();
    QString num=ui->etnum->text();
    Book newBook(name.toStdString(),publisher.toStdString(),author.toStdString(),ISBN.toLongLong(),findMark.toStdString(),loc.toStdString(),num.toInt(),num.toInt(),0);
    emit sendData_ab(newBook);  //获取newBook并且传递出去
    ui->etname->clear();
    ui->etpublish->clear();
    ui->etauthor->clear();
    ui->etISBN->clear();
    ui->etfindmark->clear();
    ui->etloc->clear();
    ui->etnum->clear();
    this->close();
}

void bm_AddBook::on_but_no_clicked()
{
    ui->etname->clear();
    ui->etpublish->clear();
    ui->etauthor->clear();
    ui->etISBN->clear();
    ui->etfindmark->clear();
    ui->etloc->clear();
    ui->etnum->clear();
    this->close();
}

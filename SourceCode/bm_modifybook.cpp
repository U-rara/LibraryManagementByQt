#include "bm_modifybook.h"
#include "ui_bm_modifybook.h"
#include "QPropertyAnimation"
#include "QMouseEvent"

bm_ModifyBook::bm_ModifyBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bm_ModifyBook)
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
void bm_ModifyBook::receiveBook_mb(Book old)
{
    oldBook=old;
    ui->etname->setText(QString::fromStdString(oldBook.get_bookName()));
    ui->etpublish->setText(QString::fromStdString(oldBook.get_publisher()));
    ui->etauthor->setText(QString::fromStdString(oldBook.get_author()));
    ui->etISBN->setText(QString::number(oldBook.get_ISBN()));
    ui->etfindmark->setText(QString::fromStdString(oldBook.get_findMark()));
    ui->etloc->setText(QString::fromStdString(oldBook.get_loc()));
    ui->etcurnum->setText(QString::number(oldBook.get_curNums()));
    ui->ettonum->setText(QString::number(oldBook.get_totalNums()));
    ui->etbot->setText(QString::number(oldBook.get_borrowedTimes()));
}

bm_ModifyBook::~bm_ModifyBook()
{
    delete ui;
}

void bm_ModifyBook::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = true;
        startPoint = event->globalPos();
        windowPoint = this->frameGeometry().topLeft();
    }
}

void bm_ModifyBook::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - startPoint;      //移动中的鼠标位置相对于初始位置的相对位置
        this->move(windowPoint + relativePos );                    //移动窗体
    }
}

void bm_ModifyBook::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = false;                                     //改变移动状态
    }
}

void bm_ModifyBook::on_but_ok_clicked()
{
    QString name=ui->etname->text();
    QString publisher=ui->etpublish->text();
    QString author=ui->etauthor->text();
    QString ISBN=ui->etISBN->text();
    QString findMark=ui->etfindmark->text();
    QString loc=ui->etloc->text();
    QString curnum=ui->etcurnum->text();
    QString tonum=ui->ettonum->text();
    QString botimes=ui->etbot->text();
    Book newBook(name.toStdString(),author.toStdString(),publisher.toStdString(),ISBN.toLongLong(),findMark.toStdString(),loc.toStdString(),curnum.toInt(),tonum.toInt(),botimes.toInt());
    emit sendData_mb(oldBook,newBook);  //获取newBook并且传递出去
    ui->etname->clear();
    ui->etpublish->clear();
    ui->etauthor->clear();
    ui->etISBN->clear();
    ui->etfindmark->clear();
    ui->etloc->clear();
    ui->etcurnum->clear();
    ui->ettonum->clear();
    ui->etbot->clear();
    this->close();
}

void bm_ModifyBook::on_but_no_clicked()
{
    ui->etname->clear();
    ui->etpublish->clear();
    ui->etauthor->clear();
    ui->etISBN->clear();
    ui->etfindmark->clear();
    ui->etloc->clear();
    ui->etcurnum->clear();
    ui->ettonum->clear();
    ui->etbot->clear();
    this->close();
}

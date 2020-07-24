#include "readercenter.h"
#include "ui_readercenter.h"
#include "qpropertyanimation.h"
#include "mainwindow.h"
#include "QMessageBox"

ReaderCenter::ReaderCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderCenter)
{
    ui->setupUi(this);
    ui->stackedWidget->setParent(this);
    ri=new ReaderInfo;
    ui->stackedWidget->addWidget(ri);

    bb=new BorrowBook;
    ui->stackedWidget->addWidget(bb);

    rb=new ReturnBook;
    ui->stackedWidget->addWidget(rb);

    bh=new BorrowHistory;
    ui->stackedWidget->addWidget(bh);

    QPropertyAnimation *animation = new QPropertyAnimation(this,"windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(0.91);
    animation->start();
    //到最后都没有找到只隐藏最大化窗口的办法，采用隐藏框架自己单独写一个最小化和关闭按钮
    //setWindowFlags(Qt::CustomizeWindowHint| Qt::WindowTitleHint| Qt::WindowMinimizeButtonHint| Qt::WindowCloseButtonHint);
    //setWindowFlags((windowFlags()&~Qt::WindowMaximizeButtonHint));
    //this->setAttribute(Qt::WA_TranslucentBackground);      //设置窗口背景透明
    this->setWindowFlags(Qt::FramelessWindowHint);         //设置无边框窗口
}

ReaderCenter::~ReaderCenter()
{
    delete ui;
}

void ReaderCenter::receiveReader(Reader rd){
    loger=rd;
}

void ReaderCenter::closeEvent(QCloseEvent *event)
{
   // QMessageBox::StandardButton button;
    int button;
    button = QMessageBox::question(this, tr("退出程序"),
                                   QString(tr("确认退出程序?")),
                                   QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No) {
          event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes) {
          event->accept();  //接受退出信号，程序退出
    }
}

void ReaderCenter::on_btn_personal_clicked()
{
    ri->set_loger(loger);
    ui->stackedWidget->setCurrentWidget(ri);
}

void ReaderCenter::on_btn_bbook_clicked()
{
    bb->set_loger(loger);
    ui->stackedWidget->setCurrentWidget(bb);
}

void ReaderCenter::on_btn_logout_clicked()
{
    this->close();
}

void ReaderCenter::on_btn_rbook_clicked()
{
    ui->stackedWidget->setCurrentWidget(rb);
}

void ReaderCenter::on_btn_his_clicked()
{
    bh->set_loger(loger);
    ui->stackedWidget->setCurrentWidget(bh);
}

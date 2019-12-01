#include "managecenter.h"
#include "ui_managecenter.h"
#include "qpropertyanimation.h"
#include "mainwindow.h"
#include "QMessageBox"

ManageCenter::ManageCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageCenter)
{
    ui->setupUi(this);
    ui->stackedWidget->setParent(this);
    bm=new BookM(this);
    ui->stackedWidget->addWidget(bm);

    ai=new AdminInfo;
    ui->stackedWidget->addWidget(ai);

    rm=new ReaderM;
    ui->stackedWidget->addWidget(rm);

    blm=new BorrowListM;
    ui->stackedWidget->addWidget(blm);

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

void ManageCenter::closeEvent(QCloseEvent *event)
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

ManageCenter::~ManageCenter()
{
    delete ui;
}

void ManageCenter::receiveAdmin(Admin ad){
    loger=ad;
}

void ManageCenter::on_btn_book_clicked()
{
    ui->stackedWidget->setCurrentWidget(bm);
}

void ManageCenter::on_btn_logout_clicked()
{
    this->close();
}

void ManageCenter::on_btn_personal_clicked()
{
    ai->set_loger(loger);
    ui->stackedWidget->setCurrentWidget(ai);
}

void ManageCenter::on_btn_reader_clicked()
{
    ui->stackedWidget->setCurrentWidget(rm);
}

void ManageCenter::on_btn_borrow_clicked()
{
    blm->set_loger(loger);
    ui->stackedWidget->setCurrentWidget(blm);
}

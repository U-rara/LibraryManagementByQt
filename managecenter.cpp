#include "managecenter.h"
#include "ui_managecenter.h"
#include "qpropertyanimation.h"

ManageCenter::ManageCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManageCenter)
{
    ui->setupUi(this);
    ui->stackedWidget->setParent(this);
    bm=new BookM(this);
    ui->stackedWidget->addWidget(bm);
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

ManageCenter::~ManageCenter()
{
    delete ui;
}

void ManageCenter::on_btn_book_clicked()
{
    ui->stackedWidget->setCurrentWidget(bm);
}

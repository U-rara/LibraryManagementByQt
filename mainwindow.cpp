#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtEvents"
#include "qpropertyanimation.h"
#include "QMouseEvent"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    isMove=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Return:{       //数字键盘Enter键
        on_button_login_clicked();
        break;
    }
    case Qt::Key_Enter: {       //Enter键
        on_button_login_clicked();
        break;
    }
    default:
        break;
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = true;
        startPoint = event->globalPos();
        windowPoint = this->frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - startPoint;      //移动中的鼠标位置相对于初始位置的相对位置
        this->move(windowPoint + relativePos );                    //移动窗体
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        isMove = false;                                     //改变移动状态
    }
}



void MainWindow::on_button_login_clicked()
{
    QString account=ui->line_account->text();
    QString password=ui->line_password->text();
    if(account.length()<1){
        QMessageBox::critical(this,"错误","请您输入账号后再登录","确认");
    }
    else if(password.length()<1){
        QMessageBox::critical(this,"错误","请您输入密码后再登录","确认");
    }
    else if(loginType=="NoType"){
        QMessageBox::critical(this,"错误","请选择登陆类型","确认");
    }
    else{
        if(loginType=="admin"){
            if(this->adm.LoginAdmin(account.toInt(),password.toStdString())){
                QPropertyAnimation *animation = new QPropertyAnimation(&mc,"windowOpacity");
                animation->setDuration(300);
                animation->setStartValue(0);
                animation->setEndValue(0.91);
                animation->start();
                this->hide();
                mc.show(); 
            }else{
                QMessageBox::critical(this,"错误","你输入的账户名或密码不正确，原因可能是：\n1、账户名输入有误；\n2、忘记密码；\n3、未区分字母大小写；\n4、未开启小键盘。\n\n如果你的密码丢失或遗忘，可寻找管理员找回密码。\n","确认");
                this->ui->button_login->setText("登录");
            }
        }else{
            if(this->rdm.LoginReader(account.toInt(),password.toStdString())){
                QPropertyAnimation *animation = new QPropertyAnimation(&rc,"windowOpacity");
                animation->setDuration(300);
                animation->setStartValue(0);
                animation->setEndValue(0.91);
                animation->start();
                this->hide();
                rc.show();
            }else{
                QMessageBox::critical(this,"错误","你输入的账户名或密码不正确，原因可能是：\n1、账户名输入有误；\n2、忘记密码；\n3、未区分字母大小写；\n4、未开启小键盘。\n\n如果你的密码丢失或遗忘，可寻找管理员找回密码。\n","确认");
                this->ui->button_login->setText("登录");
            }
        }

    }

}

void MainWindow::on_button_mini_clicked()
{
    this->showMinimized();
}

void MainWindow::on_button_close_clicked()
{
    this->close();
}

void MainWindow::on_radioButton_reader_pressed()
{
    loginType="reader";
}

void MainWindow::on_radioButton_admin_pressed()
{
    loginType="admin";
}

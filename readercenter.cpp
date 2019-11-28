#include "readercenter.h"
#include "ui_readercenter.h"

ReaderCenter::ReaderCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReaderCenter)
{
    ui->setupUi(this);
}

ReaderCenter::~ReaderCenter()
{
    delete ui;
}

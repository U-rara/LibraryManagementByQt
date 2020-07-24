#ifndef READERCENTER_H
#define READERCENTER_H

#include <QWidget>
#include "Classes/BookManagement.h"
#include "Classes/ReturnListManagement.h"
#include "Classes/BorrowListManagement.h"
#include "readerinfo.h"
#include "borrowbook.h"
#include "returnbook.h"
#include "borrowhistory.h"

namespace Ui {
class ReaderCenter;
}

class ReaderCenter : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderCenter(QWidget *parent = nullptr);
    ~ReaderCenter();
    void closeEvent(QCloseEvent *event);
private slots:
    void receiveReader(Reader);
    void on_btn_personal_clicked();

    void on_btn_bbook_clicked();

    void on_btn_logout_clicked();

    void on_btn_rbook_clicked();

    void on_btn_his_clicked();

private:
    Ui::ReaderCenter *ui;
    Reader loger;
    BookManagement bkm;
    ReturnListManagement rlm;
    BorrowListManagement blm;
    ReaderInfo *ri;
    BorrowBook *bb;
    ReturnBook *rb;
    BorrowHistory *bh;
};

#endif // READERCENTER_H

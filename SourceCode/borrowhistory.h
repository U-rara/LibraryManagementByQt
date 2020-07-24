#ifndef BORROWHISTORY_H
#define BORROWHISTORY_H

#include <QWidget>
#include "Classes/BorrowListManagement.h"

namespace Ui {
class BorrowHistory;
}

class BorrowHistory : public QWidget
{
    Q_OBJECT

public:
    explicit BorrowHistory(QWidget *parent = nullptr);
    ~BorrowHistory();
    void set_loger(Reader rd);
private slots:
    void on_button_todo_clicked();

    void on_button_ok_clicked();

    void on_button_no_clicked();

    void on_button_searchid_clicked();

    void on_button_all_clicked();

private:
    Ui::BorrowHistory *ui;
    BorrowListManagement blm;
    ReaderManagement rdm;
    BookManagement bkm;
    Reader loger;
    list<BorrowList> mb;
};

#endif // BORROWHISTORY_H

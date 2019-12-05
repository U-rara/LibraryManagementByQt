#ifndef BORROWBOOK_H
#define BORROWBOOK_H

#include <QWidget>
#include "Classes/BookManagement.h"
#include "Classes/Reader.h"
#include "Classes/BorrowListManagement.h"

namespace Ui {
class BorrowBook;
}

class BorrowBook : public QWidget
{
    Q_OBJECT

public:
    explicit BorrowBook(QWidget *parent = nullptr);
    ~BorrowBook();
    void set_loger(Reader rd);
private slots:
    void on_button_req_clicked();

private:
    Ui::BorrowBook *ui;
    BookManagement bkm;
    BorrowListManagement blm;
    Reader loger;
};

#endif // BORROWBOOK_H

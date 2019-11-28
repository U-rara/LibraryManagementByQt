#ifndef BOOKM_H
#define BOOKM_H

#include <QWidget>
#include <Classes/BookManagement.h>
#include "bm_addbook.h"

namespace Ui {
class BookM;
}

class BookM : public QWidget
{
    Q_OBJECT

public:
    explicit BookM(QWidget *parent = nullptr);
    ~BookM();

private slots:
    void receiveData(Book newBook);
    void on_button_add_clicked();

private:
    Ui::BookM *ui;
    BookManagement bkm;
    bm_AddBook *ab;
};

#endif // BOOKM_H

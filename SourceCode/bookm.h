#ifndef BOOKM_H
#define BOOKM_H

#include <QWidget>
#include <Classes/BookManagement.h>
#include "bm_addbook.h"
#include "bm_modifybook.h"

namespace Ui {
class BookM;
}

class BookM : public QWidget
{
    Q_OBJECT

public:
    explicit BookM(QWidget *parent = nullptr);
    ~BookM();
signals:
    void sendBook_mb(Book); //传信号

private slots:
    void receiveData_ab(Book newBook);
    void receiveData_mb(Book oldBook,Book newBook);
    void on_button_add_clicked();

    void on_button_delete_clicked();

    void on_button_mod_clicked();

    void on_button_search_clicked();

    void on_button_all_clicked();

private:
    Ui::BookM *ui;
    BookManagement bkm;
    bm_AddBook *ab;
    bm_ModifyBook *mb;
};

#endif // BOOKM_H

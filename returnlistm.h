#ifndef RETURNLISTM_H
#define RETURNLISTM_H

#include <QWidget>
#include "Classes/ReturnListManagement.h"

namespace Ui {
class ReturnListM;
}

class ReturnListM : public QWidget
{
    Q_OBJECT

public:
    explicit ReturnListM(QWidget *parent = nullptr);
    ~ReturnListM();
    void set_loger(Admin);
private slots:
    void on_button_ok_clicked();

    void on_button_no_clicked();

    void on_button_todo_clicked();

    void on_button_done_clicked();

    void on_button_all_clicked();

    void on_button_searchid_clicked();

private:
    Ui::ReturnListM *ui;
    ReturnListManagement rlm;
    BorrowListManagement blm;
    ReaderManagement rdm;
    BookManagement bkm;
    Admin loger;
};

#endif // RETURNLISTM_H

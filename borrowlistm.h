#ifndef BORROWLISTM_H
#define BORROWLISTM_H

#include <QWidget>
#include "Classes/BorrowListManagement.h"

namespace Ui {
class BorrowListM;
}

class BorrowListM : public QWidget
{
    Q_OBJECT

public:
    explicit BorrowListM(QWidget *parent = nullptr);
    ~BorrowListM();
    void set_loger(Admin);
private slots:
    void on_button_ok_clicked();

    void on_button_no_clicked();

private:
    Ui::BorrowListM *ui;
    BorrowListManagement blm;
    Admin loger;
};

#endif // BORROWLISTM_H

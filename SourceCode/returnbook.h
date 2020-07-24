#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include <QWidget>
#include "Classes/ReturnListManagement.h"

namespace Ui {
class ReturnBook;
}

class ReturnBook : public QWidget
{
    Q_OBJECT

public:
    explicit ReturnBook(QWidget *parent = nullptr);
    ~ReturnBook();

private slots:

    void on_but_ok_clicked();

private:
    Ui::ReturnBook *ui;
    ReturnListManagement rlm;
};

#endif // RETURNBOOK_H

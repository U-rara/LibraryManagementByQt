#ifndef MANAGECENTER_H
#define MANAGECENTER_H

#include <QWidget>
#include "bookm.h"

namespace Ui {
class ManageCenter;
}

class ManageCenter : public QWidget
{
    Q_OBJECT

public:
    explicit ManageCenter(QWidget *parent = nullptr);
    ~ManageCenter();

private slots:
    void on_btn_book_clicked();

private:
    Ui::ManageCenter *ui;
    BookM *bm;
};

#endif // MANAGECENTER_H

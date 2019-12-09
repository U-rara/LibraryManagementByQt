#ifndef ADMININFO_H
#define ADMININFO_H

#include <QWidget>
#include "Classes/AdminManagement.h"

namespace Ui {
class AdminInfo;
}

class AdminInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AdminInfo(QWidget *parent = nullptr);
    ~AdminInfo();
    void set_loger(Admin ad);

private slots:
    void on_but_ok_clicked();

private:
    Ui::AdminInfo *ui;
    Admin loger;
    AdminManagement adm;
};

#endif // ADMININFO_H

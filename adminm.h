#ifndef ADMINM_H
#define ADMINM_H

#include <QWidget>
#include "Classes/AdminManagement.h"
#include "am_addadmin.h"

namespace Ui {
class AdminM;
}

class AdminM : public QWidget
{
    Q_OBJECT

public:
    explicit AdminM(QWidget *parent = nullptr);
    ~AdminM();

private slots:
    void on_button_add_clicked();
    void receiveAdmin_aa(Admin);
    void on_button_delete_clicked();

    void on_button_setpas_clicked();

    void on_button_all_clicked();

    void on_button_search_clicked();

private:
    Ui::AdminM *ui;
    AdminManagement adm;
    am_AddAdmin* aa;
};

#endif // ADMINM_H

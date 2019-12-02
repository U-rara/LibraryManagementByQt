#ifndef READERM_H
#define READERM_H

#include <QWidget>
#include "Classes/ReaderManagement.h"
#include "rm_addreader.h"
#include "rm_modifyreader.h"

namespace Ui {
class ReaderM;
}

class ReaderM : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderM(QWidget *parent = nullptr);
    ~ReaderM();

signals:
    void sendReader_mr(Reader); //传信号

private slots:
    void on_button_add_clicked();
    void receiveReader_ar(Reader);
    void receiveReader_mr(Reader,Reader);
    void on_button_delete_clicked();

    void on_button_all_clicked();

    void on_button_modify_clicked();

    void on_button_search_clicked();

    void on_button_setpas_clicked();

private:
    Ui::ReaderM *ui;
    ReaderManagement rdm;
    rm_AddReader *ar;
    rm_ModifyReader *mr;
};

#endif // READERM_H

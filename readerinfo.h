#ifndef READERINFO_H
#define READERINFO_H

#include <QWidget>
#include "Classes/ReaderManagement.h"

namespace Ui {
class ReaderInfo;
}

class ReaderInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderInfo(QWidget *parent = nullptr);
    ~ReaderInfo();
    void set_loger(Reader rd);
private slots:
    void on_but_ok_clicked();

private:
    Ui::ReaderInfo *ui;
    Reader loger;
    ReaderManagement rdm;
};

#endif // READERINFO_H

#ifndef BM_MODIFYBOOK_H
#define BM_MODIFYBOOK_H

#include <QWidget>
#include "Classes/BookManagement.h"

namespace Ui {
class bm_ModifyBook;
}

class bm_ModifyBook : public QWidget
{
    Q_OBJECT

public:
    explicit bm_ModifyBook(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    ~bm_ModifyBook();

private slots:
    void on_but_ok_clicked();
    void receiveBook_mb(Book oldBook);
    void on_but_no_clicked();

signals:
    void sendData_mb(Book,Book); //传信号

private:
    Ui::bm_ModifyBook *ui;
    QPoint startPoint;
    QPoint windowPoint;
    bool isMove;
    Book oldBook;
};

#endif // BM_MODIFYBOOK_H

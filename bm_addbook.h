#ifndef BM_ADDBOOK_H
#define BM_ADDBOOK_H

#include <QWidget>
#include "Classes/BookManagement.h"

namespace Ui {
class bm_AddBook;
}

class bm_AddBook : public QWidget
{
    Q_OBJECT

public:
    explicit bm_AddBook(QWidget *parent = nullptr);
    ~bm_AddBook();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_but_ok_clicked();

    void on_but_no_clicked();

signals:
    void sendData(Book); //传信号

private:
    Ui::bm_AddBook *ui;
    QPoint startPoint;
    QPoint windowPoint;
    bool isMove;
};

#endif // BM_ADDBOOK_H

#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QWidget>
#include "bookm.h"

namespace Ui {
class AddBook;
}

class AddBook : public QWidget
{
    Q_OBJECT

public:
    explicit AddBook(QWidget *parent = nullptr);
    ~AddBook();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void on_but_no_clicked();

    void on_but_ok_clicked();

signals:

    void sendData(Book); //传信号

private:
    Ui::AddBook *ui;
    QPoint startPoint;
    QPoint windowPoint;
    bool isMove;
};

#endif // ADDBOOK_H

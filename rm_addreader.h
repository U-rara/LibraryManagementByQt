#ifndef RM_ADDREADER_H
#define RM_ADDREADER_H

#include <QWidget>
#include "Classes/Reader.h"

namespace Ui {
class rm_AddReader;
}

class rm_AddReader : public QWidget
{
    Q_OBJECT

public:
    explicit rm_AddReader(QWidget *parent = nullptr);
    ~rm_AddReader();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_but_ok_clicked();

    void on_but_no_clicked();

signals:
    void sendReader_ar(Reader);

private:
    Ui::rm_AddReader *ui;
    QPoint startPoint;
    QPoint windowPoint;
    bool isMove;
};

#endif // RM_ADDREADER_H

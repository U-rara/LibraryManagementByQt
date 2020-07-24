#ifndef RM_MODIFYREADER_H
#define RM_MODIFYREADER_H

#include <QWidget>
#include "Classes/ReaderManagement.h"

namespace Ui {
class rm_ModifyReader;
}

class rm_ModifyReader : public QWidget
{
    Q_OBJECT

public:
    explicit rm_ModifyReader(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    ~rm_ModifyReader();
signals:
    void sendReader_mr(Reader,Reader); //传信号
private slots:
    void on_but_ok_clicked();
    void receiveReader_mr(Reader oldReader);
    void on_but_no_clicked();

private:
    Ui::rm_ModifyReader *ui;
    QPoint startPoint;
    QPoint windowPoint;
    bool isMove;
    Reader oldReader;
};

#endif // RM_MODIFYREADER_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "Classes/AdminManagement.h"
#include "managecenter.h"
#include "readercenter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:

    void keyPressEvent(QKeyEvent *event);
    void on_button_login_clicked();

    void on_button_mini_clicked();

    void on_button_close_clicked();


    void on_radioButton_reader_pressed();

    void on_radioButton_admin_pressed();

private:
    Ui::MainWindow *ui;
    QString loginType="NoType";
    bool isMove;
    AdminManagement adm;
    ReaderManagement rdm;
    ReaderCenter rc;
    ManageCenter mc;
    QPoint startPoint;
    QPoint windowPoint;
};
#endif // MAINWINDOW_H

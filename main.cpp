#include "mainwindow.h"

#include <QApplication>
#include "QMetaType"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qRegisterMetaType<Book>("Book");
    w.show();
    return a.exec();
}

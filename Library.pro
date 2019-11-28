QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bm_addbook.cpp \
    bookm.cpp \
    main.cpp \
    mainwindow.cpp \
    managecenter.cpp \
    readercenter.cpp

HEADERS += \
    Classes/Admin.h \
    Classes/AdminManagement.h \
    Classes/Book.h \
    Classes/BookManagement.h \
    Classes/BorrowList.h \
    Classes/BorrowListManagement.h \
    Classes/Reader.h \
    Classes/ReaderManagement.h \
    Classes/tm.h \
    bm_addbook.h \
    bookm.h \
    mainwindow.h \
    managecenter.h \
    readercenter.h

FORMS += \
    bm_addbook.ui \
    bookm.ui \
    mainwindow.ui \
    managecenter.ui \
    readercenter.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    Classes/Admin/data.txt \
    Classes/Book/data.txt \
    Classes/BorrowList/data.txt \
    Classes/Reader/data.txt

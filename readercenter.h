#ifndef READERCENTER_H
#define READERCENTER_H

#include <QWidget>

namespace Ui {
class ReaderCenter;
}

class ReaderCenter : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderCenter(QWidget *parent = nullptr);
    ~ReaderCenter();

private:
    Ui::ReaderCenter *ui;
};

#endif // READERCENTER_H

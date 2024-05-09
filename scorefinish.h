#ifndef SCOREFINISH_H
#define SCOREFINISH_H

#include <QWidget>

namespace Ui {
class scoreFinish;
}

class scoreFinish : public QWidget
{
    Q_OBJECT

public:
    explicit scoreFinish(QWidget *parent = nullptr, QString user="");
    ~scoreFinish();

private:
    Ui::scoreFinish *ui;
};

#endif // SCOREFINISH_H

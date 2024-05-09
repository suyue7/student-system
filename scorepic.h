#ifndef SCOREPIC_H
#define SCOREPIC_H

#include <QWidget>

namespace Ui {
class scorePic;
}

class scorePic : public QWidget
{
    Q_OBJECT

public:
    explicit scorePic(QWidget *parent = nullptr, QString user="");
    ~scorePic();

private:
    Ui::scorePic *ui;
};

#endif // SCOREPIC_H

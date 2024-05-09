#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>

namespace Ui {
class helpwidget;
}

class helpwidget : public QWidget
{
    Q_OBJECT

public:
    explicit helpwidget(QWidget *parent = nullptr);
    ~helpwidget();

private slots:
    void on_exitBtn_clicked();

private:
    Ui::helpwidget *ui;
};

#endif // HELPWIDGET_H

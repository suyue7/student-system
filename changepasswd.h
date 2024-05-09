#ifndef CHANGEPASSWD_H
#define CHANGEPASSWD_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "mainwindow.h"

namespace Ui {
class changepasswd;
}

class changepasswd : public QDialog
{
    Q_OBJECT

public:
    explicit changepasswd(QWidget *parent = nullptr);
    ~changepasswd();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::changepasswd *ui;
};

#endif // CHANGEPASSWD_H

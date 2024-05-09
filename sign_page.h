#ifndef SIGN_PAGE_H
#define SIGN_PAGE_H
#include"forgetview.h"
#include <QWidget>
#include<QString>
#include<QDebug>
#include"dboperator.h"
#include "mainpage2.h"
#include "studentpage.h"
#include "teacherpage.h"
#include "announcepage.h"
namespace Ui {
class Sign_page;
}

class Sign_page : public QWidget
{
    Q_OBJECT

public:
    DBOperator myDatabase;
    explicit Sign_page(QWidget *parent = nullptr);
    ~Sign_page();
    void loginBtn_clicked();
signals:
    void try_login();
private slots:
    void on_loginBtn_clicked();

    void on_exitBtn_clicked();

    void on_forgetButton_clicked();

private:
    Ui::Sign_page *ui;
};

#endif // SIGN_PAGE_H

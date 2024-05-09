#include "changepasswd.h"
#include "ui_changepasswd.h"
#include "mainwindow.h"

changepasswd::changepasswd(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::changepasswd)
{
    ui->setupUi(this);

    ui->oldlineEdit->setPlaceholderText("请输入原密码");
    ui->newlineEdit->setPlaceholderText("请输入新密码");
    ui->newlineEdit2->setPlaceholderText("请再次输入新密码");
}

changepasswd::~changepasswd()
{
    delete ui;
}

void changepasswd::on_pushButton_clicked()
{
    QString old = ui->oldlineEdit->text();
    QString new1 = ui->newlineEdit->text();
    QString new2 = ui->newlineEdit2->text();
    if(old.isEmpty()||new1.isEmpty()||new2.isEmpty()){
        QMessageBox::warning(this, "警告", "信息填写不完整！");
        return;
    }
    std::regex r("^[a-zA-Z0-9]{6,15}$");
    std::string p =new1.toStdString();
    bool bValid=std::regex_match(p,r);
    if(!bValid){
        QMessageBox::warning(this, "警告", "密码由6-15位数字或字母组成！请重输");
        return;
    }
    // if(new1.length()<6||new1.length()>15){
    //     QMessageBox::warning(this, "警告", "新密码长度需为6-15位！请重输");
    //     return;
    // }
    QSqlQuery query;
    if(MainWindow::sfLB==0){
        QString sql = QString("select * from student_table where sid='%1' and spasswd='%2';").arg(MainWindow::sfID, old);
        query.exec(sql);
        if(!query.next()){
            QMessageBox::warning(this, "警告", "原密码错误！请重输");
            return;
        }
        if(new1 != new2){
            QMessageBox::warning(this, "警告", "新密码两次输入不相同！请重输");
            return;
        }
        sql = QString("UPDATE student_table SET spasswd='%1' WHERE sid='%2';").arg(new1,MainWindow::sfID);
        if(query.exec(sql))
            QMessageBox::information(this, "提示", "修改密码成功！");
    }
    else if(MainWindow::sfLB==1){
        QString sql = QString("select * from teacher_table where tid='%1' and tpasswd='%2';").arg(MainWindow::sfID, old);
        query.exec(sql);
        if(!query.next()){
            QMessageBox::warning(this, "警告", "原密码错误！请重输");
            return;
        }
        if(new1 != new2){
            QMessageBox::warning(this, "警告", "新密码两次输入不相同！请重输");
            return;
        }
        sql = QString("UPDATE teacher_table SET tpasswd='%1' WHERE tid='%2';").arg(new1,MainWindow::sfID);
        if(query.exec(sql))
            QMessageBox::information(this, "提示", "修改密码成功！");
    }
    else if(MainWindow::sfLB==2){
        QString sql = QString("select * from admin_table where admin_id='%1' and admin_passwd='%2';").arg(MainWindow::sfID, old);
        query.exec(sql);
        if(!query.next()){
            QMessageBox::warning(this, "警告", "原密码错误！请重输");
            return;
        }
        if(new1 != new2){
            QMessageBox::warning(this, "警告", "新密码两次输入不相同！请重输");
            return;
        }
        sql = QString("UPDATE admin_table SET admin_passwd='%1' WHERE admin_id='%2';").arg(new1,MainWindow::sfID);
        if(query.exec(sql))
            QMessageBox::information(this, "提示", "修改密码成功！");
    }
}


void changepasswd::on_pushButton_2_clicked()
{
    close();
}


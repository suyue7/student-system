#include "forgetview.h"
#include "ui_forgetview.h"

Forgetview::Forgetview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Forgetview)
{
    ui->setupUi(this);
     this->myDataBase.DBOpen();
}

Forgetview::~Forgetview()
{
    delete ui;
}

void Forgetview::on_pushButton_2_clicked()
{
    QString id=ui->lineEdit->text();
    QString phone=ui->lineEdit_2->text();
    QString code1=ui->lineEdit_3->text();
    QString code2=ui->lineEdit_4->text();
    QSqlQuery query1;
    QString sql1=QString("select * from student_table where sid='%1' and sphonenumber='%2'").arg(id).arg(phone);
    if(query1.exec(sql1))
    {
        if(code1==code2)
        {
            QSqlQuery query;
            QString sql=QString("update student_table set spasswd='%1' where sid='%2' ").arg(code1).arg(id);
            query.exec(sql);
            QMessageBox::information(NULL,"登录成功","登录成功！！",QMessageBox::Yes);
            mainpage2 *w=new mainpage2();
            w->show();
            return;
        }
        else
        {
            QMessageBox::warning(NULL,"登录失败","两次用户名不一致");
        }
    }
    QSqlQuery query2;
    QString sql2=QString("select * from teacher_table where tid='%1' and tphonenumber='%2'").arg(id).arg(phone);
    if(query2.exec(sql2))
    {
        if(code1==code2)
        {
            QSqlQuery query;
            QString sql=QString("update teacher_table set tpasswd='%1' where tid='%2' ").arg(code1).arg(id);
            query.exec(sql);
            QMessageBox::information(NULL,"登录成功","登录成功！！",QMessageBox::Yes);
            mainpage2 *w=new mainpage2();
            w->show();
            return;
        }
        else
        {
            QMessageBox::warning(NULL,"登录失败","两次用户名不一致");
        }
    }
    else
    {
         QMessageBox::warning(NULL,"验证失败","用户名或者电话号码错误");
    }
}


void Forgetview::on_pushButton_clicked()
{
    Sign_page *w=new Sign_page();
    w->show();
    myDataBase.DBClose();
    this->close();
}



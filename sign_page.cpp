#include "sign_page.h"
#include "ui_sign_page.h"
#include"dboperator.h"
#include<qDebug>
#include<QMessageBox>
#include<QSqlQueryModel>
Sign_page::Sign_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sign_page)
{
    ui->setupUi(this);
    this->myDatabase.DBOpen();
}

Sign_page::~Sign_page()
{
    delete ui;
    this->myDatabase.DBClose();
}
void Sign_page::on_loginBtn_clicked()
{
    QString usertype;
    if(ui->adminBtn->isChecked())
    {
        usertype="admin";
    }else if(ui->teacherBtn->isChecked())
    {
        usertype="teacher";
    }else if(ui->studentBtn->isChecked())
    {
        usertype="student";
    }
    QString userInputid=ui->idEdit->text().trimmed();
    QString userInputcode=ui->codeEdit->text().trimmed();
    qDebug()<<"用户id为"<<userInputid;
    qDebug()<<"用户密码为"<<userInputcode;
    qDebug()<<"用户类别为"<<usertype;

       if(ui->adminBtn->isChecked())
    {
        //获取数据库中的信息
        QSqlQuery sql;
        //使用SELETE语言在对应表中查找id
        sql.prepare("select * from admin_table where admin_id = :userInputid");
        //给这个字符串赋予实际变量和含义
        sql.bindValue(":userInputid",userInputid);
        //给这个字符串赋予实际变量和含义
        sql.exec();
        QString userid;
        QString usercode;
        //每一条寻找是否 有满足条件的
        if(sql.next())
        {
            userid=sql.value("admin_id").toString();
            usercode=sql.value("admin_passwd").toString();
            qDebug()<<"数据库找到的账号"<<userid;
            qDebug()<<"数据库找到的密码"<<usercode;
        }
        sql.clear();
        if(userInputcode==usercode&&userInputid==userid)
        {
            QMessageBox::information(NULL,"登录成功","登录成功！！",QMessageBox::Yes);
            mainpage2 *w=new mainpage2();
            w->show();
            myDatabase.DBClose();
            this->close();
            //登录成功之后进入新的界，可以开始new
        }
        else
        {
            QMessageBox::warning(NULL,"登录失败","用户名或者密码错误");
        }
    }
}
void Sign_page::on_exitBtn_clicked()
{
       this->close();
}


void Sign_page::on_forgetButton_clicked()
{
       Forgetview *w=new Forgetview();
       w->show();
       myDatabase.DBClose();
       this->close();
}


#include "applylesson.h"
#include "ui_applylesson.h"
#include "mainpage2.h"
#include <QMessageBox>
#include <QSqlQuery>

applylesson::applylesson(QWidget *parent,QString cid) :
    QWidget(parent),
    ui(new Ui::applylesson)
{
    ui->setupUi(this);

    this->cid=cid;
    this->setWindowTitle("同意开课");
    ui->subBtn->setIcon(QIcon("image/right.png"));
    ui->subBtn->setLayoutDirection(Qt::RightToLeft);
    ui->cancelBtn->setIcon(QIcon("image/wrong.png"));
    ui->cancelBtn->setLayoutDirection(Qt::RightToLeft);

    ui->week1->addItem("星期一");
    ui->week1->addItem("星期二");
    ui->week1->addItem("星期三");
    ui->week1->addItem("星期四");
    ui->week1->addItem("星期五");
    ui->week1->addItem("星期六");
    ui->week1->addItem("星期日");

    ui->day1->addItem("第一节");
    ui->day1->addItem("第二节");
    ui->day1->addItem("第三节");
    ui->day1->addItem("第四节");
    ui->day1->addItem("第五节");
    ui->day1->addItem("第六节");
    ui->day1->addItem("第七节");
    ui->day1->addItem("第八节");
    ui->day1->addItem("第九节");

    ui->week2->addItem("星期一");
    ui->week2->addItem("星期二");
    ui->week2->addItem("星期三");
    ui->week2->addItem("星期四");
    ui->week2->addItem("星期五");
    ui->week2->addItem("星期六");
    ui->week2->addItem("星期日");

    ui->day2->addItem("第一节");
    ui->day2->addItem("第二节");
    ui->day2->addItem("第三节");
    ui->day2->addItem("第四节");
    ui->day2->addItem("第五节");
    ui->day2->addItem("第六节");
    ui->day2->addItem("第七节");
    ui->day2->addItem("第八节");
    ui->day2->addItem("第九节");

    ui->week3->addItem("星期一");
    ui->week3->addItem("星期二");
    ui->week3->addItem("星期三");
    ui->week3->addItem("星期四");
    ui->week3->addItem("星期五");
    ui->week3->addItem("星期六");
    ui->week3->addItem("星期日");

    ui->day3->addItem("第一节");
    ui->day3->addItem("第二节");
    ui->day3->addItem("第三节");
    ui->day3->addItem("第四节");
    ui->day3->addItem("第五节");
    ui->day3->addItem("第六节");
    ui->day3->addItem("第七节");
    ui->day3->addItem("第八节");
    ui->day3->addItem("第九节");

}

applylesson::~applylesson()
{
    delete ui;
}

void applylesson::on_subBtn_clicked()
{
    QString week_1=ui->week1->currentText();
    QString day_1=ui->day1->currentText();
    QString week_2=ui->week2->currentText();
    QString day_2=ui->day2->currentText();
    QString week_3=ui->week3->currentText();
    QString day_3=ui->day3->currentText();
    if (week_1==""&&week_2==""&&week_3==""&&day_1==""&&day_2==""&&day_3=="")
    {
        QMessageBox::warning(NULL,"警告","请至少选择一个时间！");
        return;
    }
    if (week_1!=""&&day_1=="")
    {
        QMessageBox::warning(NULL,"警告","请选择星期对应的节次！");
        return;
    }
    if (week_2!=""&&day_2=="")
    {
        QMessageBox::warning(NULL,"警告","请选择星期对应的节次！");
        return;
    }
    if (week_3!=""&&day_3=="")
    {
        QMessageBox::warning(NULL,"警告","请选择星期对应的节次！");
        return;
    }

    if (week_1==""&&day_1!="")
    {
        QMessageBox::warning(NULL,"警告","请选择节次对应的星期！");
        return;
    }
    if (week_2==""&&day_2!="")
    {
        QMessageBox::warning(NULL,"警告","请选择节次对应的星期！");
        return;
    }
    if (week_3==""&&day_3!="")
    {
        QMessageBox::warning(NULL,"警告","请选择节次对应的星期！");
        return;
    }

    if (week_1!=""&&week_1==week_2&&day_1==day_2) {QMessageBox::warning(NULL,"警告","节次一和节次二时间重复！");return;}
    if (week_1!=""&&week_1==week_3&&day_1==day_3) {QMessageBox::warning(NULL,"警告","节次一和节次三时间重复！");return;}
    if (week_2!=""&&week_2==week_3&&day_2==day_3) {QMessageBox::warning(NULL,"警告","节次二和节次三时间重复！");return;}

    int w1,w2,w3,d1,d2,d3;
    if (week_1=="星期一") w1=1;
    if (week_1=="星期二") w1=2;
    if (week_1=="星期三") w1=3;
    if (week_1=="星期四") w1=4;
    if (week_1=="星期五") w1=5;
    if (week_1=="星期六") w1=6;
    if (week_1=="星期日") w1=7;

    if (week_2=="星期一") w2=1;
    if (week_2=="星期二") w2=2;
    if (week_2=="星期三") w2=3;
    if (week_2=="星期四") w2=4;
    if (week_2=="星期五") w2=5;
    if (week_2=="星期六") w2=6;
    if (week_2=="星期日") w2=7;

    if (week_3=="星期一") w3=1;
    if (week_3=="星期二") w3=2;
    if (week_3=="星期三") w3=3;
    if (week_3=="星期四") w3=4;
    if (week_3=="星期五") w3=5;
    if (week_3=="星期六") w3=6;
    if (week_3=="星期日") w3=7;

    if (day_1=="第一节") d1=1;
    if (day_1=="第二节") d1=2;
    if (day_1=="第三节") d1=3;
    if (day_1=="第四节") d1=4;
    if (day_1=="第五节") d1=5;
    if (day_1=="第六节") d1=6;
    if (day_1=="第七节") d1=7;
    if (day_1=="第八节") d1=8;
    if (day_1=="第九节") d1=9;

    if (day_2=="第一节") d2=1;
    if (day_2=="第二节") d2=2;
    if (day_2=="第三节") d2=3;
    if (day_2=="第四节") d2=4;
    if (day_2=="第五节") d2=5;
    if (day_2=="第六节") d2=6;
    if (day_2=="第七节") d2=7;
    if (day_2=="第八节") d2=8;
    if (day_2=="第九节") d2=9;

    if (day_3=="第一节") d3=1;
    if (day_3=="第二节") d3=2;
    if (day_3=="第三节") d3=3;
    if (day_3=="第四节") d3=4;
    if (day_3=="第五节") d3=5;
    if (day_3=="第六节") d3=6;
    if (day_3=="第七节") d3=7;
    if (day_3=="第八节") d3=8;
    if (day_3=="第九节") d3=9;

    QSqlQuery query;
    QString sql;
    sql=QString("SELECT * FROM class_table WHERE cid='%1'").arg(cid);
    query.exec(sql);
    query.first();
    QString thisLo=query.value("clocation").toString();
    QString thisTe=query.value("tid").toString();
    int flag1=0,flag2=0,flag3=0;

    if (week_1!="")   //判断节次一的课室、老师是否冲突
    {
        query.clear();
        sql=QString("SELECT * FROM arr_table WHERE clocation='%1'").arg(thisLo);
        query.exec(sql);
        while (query.next())
        {
            if (query.value("weekday").toInt()==w1&&query.value("classTime").toInt()==d1)
            {
                QMessageBox::warning(NULL,"警告","节次一所选时间的地点已被占用！");
                return;
            }
        }

        query.clear();
        sql=QString("SELECT * FROM arr_table WHERE tid='%1'").arg(thisTe);
        query.exec(sql);
        while (query.next())
        {
            if (query.value("weekday").toInt()==w1&&query.value("classTime").toInt()==d1)
            {
                QMessageBox::warning(NULL,"警告","节次一所选时间与该教师其他课程冲突！");
                return;
            }
        }
        flag1=1;

    }

    if (week_2!="")   //判断节次一的课室、老师是否冲突
    {
        query.clear();
        sql=QString("SELECT * FROM arr_table WHERE clocation='%1'").arg(thisLo);
        query.exec(sql);
        while (query.next())
        {
            if (query.value("weekday").toInt()==w2&&query.value("classTime").toInt()==d2)
            {
                QMessageBox::warning(NULL,"警告","节次二所选时间的地点已被占用！");
                return;
            }
        }

        query.clear();
        sql=QString("SELECT * FROM arr_table WHERE tid='%1'").arg(thisTe);
        query.exec(sql);
        while (query.next())
        {
            if (query.value("weekday").toInt()==w2&&query.value("classTime").toInt()==d2)
            {
                QMessageBox::warning(NULL,"警告","节次二所选时间与该教师其他课程冲突！");
                return;
            }
        }
        flag2=1;
    }

    if (week_3!="")   //判断节次一的课室、老师是否冲突
    {
        query.clear();
        sql=QString("SELECT * FROM arr_table WHERE clocation='%1'").arg(thisLo);
        query.exec(sql);
        while (query.next())
        {
            if (query.value("weekday").toInt()==w3&&query.value("classTime").toInt()==d3)
            {
                QMessageBox::warning(NULL,"警告","节次三所选时间的地点已被占用！");
                return;
            }
        }

        query.clear();
        sql=QString("SELECT * FROM arr_table WHERE tid='%1'").arg(thisTe);
        query.exec(sql);
        while (query.next())
        {
            if (query.value("weekday").toInt()==w3&&query.value("classTime").toInt()==d3)
            {
                QMessageBox::warning(NULL,"警告","节次三所选时间与该教师其他课程冲突！");
                return;
            }
        }
        flag3=1;
    }

    QMessageBox::StandardButton box;
    box=QMessageBox::question(this, "提示", "确定要开设这门课程吗?", QMessageBox::Yes|QMessageBox::No);
    if (box==QMessageBox::No) return;

    query.clear();
    sql=QString("UPDATE class_table SET is_apply=1 WHERE cid='%1'").arg(cid);
    if (query.exec(sql))
        qDebug()<<"开课成功";
    else QMessageBox::warning(NULL,"开课失败","修改数据库信息失败");

    if (week_1!=""&&flag1==1)
    {
        query.clear();
        sql=QString("INSERT INTO arr_table(cid,tid,weekday,classtime,clocation) values('%1','%2','%3','%4','%5')").arg(cid).arg(thisTe).arg(w1).arg(d1).arg(thisLo);
        query.exec(sql);
    }
    if (week_2!=""&&flag2==1)
    {
        query.clear();
        sql=QString("INSERT INTO arr_table(cid,tid,weekday,classtime,clocation) values('%1','%2','%3','%4','%5')").arg(cid).arg(thisTe).arg(w2).arg(d2).arg(thisLo);
        query.exec(sql);
    }
    if (week_3!=""&&flag3==1)
    {
        query.clear();
        sql=QString("INSERT INTO arr_table(cid,tid,weekday,classtime,clocation) values('%1','%2','%3','%4','%5')").arg(cid).arg(thisTe).arg(w3).arg(d3).arg(thisLo);
        query.exec(sql);
    }

    emit closed();
    this->close();
}


void applylesson::on_cancelBtn_clicked()
{
    this->close();
}


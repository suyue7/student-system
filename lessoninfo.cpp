#include "lessoninfo.h"
#include "ui_lessoninfo.h"
#include "mainwindow.h"

LessonInfo::LessonInfo(QString lid, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LessonInfo)
{
    ui->setupUi(this);

    lessID = getLessonId(lid);
    setContent();
}

LessonInfo::~LessonInfo()
{
    delete ui;
}

void LessonInfo::setContent(){
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    QStringList VStrList;
    VStrList.push_back(QString("课程名"));
    VStrList.push_back(QString("课程号"));
    VStrList.push_back(QString("上课地点"));
    VStrList.push_back(QString("上课时间"));
    VStrList.push_back(QString("课程类型"));
    VStrList.push_back(QString("学分"));
    VStrList.push_back(QString("考核方式"));
    VStrList.push_back(QString("课程容量"));
    VStrList.push_back(QString("已选人数"));
    //设置行列数(只有列存在的前提下，才可以设置列标签)
    int VlabelCnt = VStrList.count();
    ui->tableWidget->setRowCount(VlabelCnt);
    ui->tableWidget->setColumnCount(1);
    //设置列标签
    ui->tableWidget->setVerticalHeaderLabels(VStrList);
    //表格充满布局
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //时间
    QSqlQuery tmpsql;
    QString sqla=QString("SELECT * FROM arr_table WHERE cid='%1'").arg(lessID);  //课程id
    tmpsql.exec(sqla);
    QString tmpstr;
    while (tmpsql.next())
    {
        int hh=tmpsql.value("weekday").toInt();
        if (hh==1) tmpstr.append("周一");
        if (hh==2) tmpstr.append("周二");
        if (hh==3) tmpstr.append("周三");
        if (hh==4) tmpstr.append("周四");
        if (hh==5) tmpstr.append("周五");
        if (hh==6) tmpstr.append("周六");
        if (hh==7) tmpstr.append("周日");
        tmpstr.append("第");
        QString dd=tmpsql.value("classtime").toString();
        tmpstr.append(dd);
        tmpstr.append("节;");
    }
    ui->tableWidget->setItem(0,3,new QTableWidgetItem(tmpstr));

    //地点
    tmpsql.clear();
    sqla=QString("SELECT * FROM arr_table WHERE cid='%1'").arg(lessID);  //课程id
    tmpsql.exec(sqla);
    tmpstr.clear();
    while (tmpsql.next())
    {
        tmpstr.append(tmpsql.value("clocation").toString());
        tmpstr.append(";");
    }
    ui->tableWidget->setItem(0,2,new QTableWidgetItem(tmpstr));

    QSqlQuery query;
    QString sql = QString("SELECT * FROM class_table WHERE cid='%1';").arg(lessID);
    qDebug() << lessID;
    query.exec(sql);
    if(query.next() && query.value("is_open").toInt()!=(int)0){
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(query.value("cname").toString()));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(lessID));
        ui->tableWidget->setItem(0, 4, new QTableWidgetItem(query.value("cclassify").toString()));
        ui->tableWidget->setItem(0, 5, new QTableWidgetItem(query.value("cscore").toString()));
        ui->tableWidget->setItem(0, 6, new QTableWidgetItem(query.value("kcfs").toString()));
        ui->tableWidget->setItem(0, 7, new QTableWidgetItem(query.value("ccapacity").toString()));
    }
}

QString LessonInfo::getLessonId(QString lvstr){
    int endp = lvstr.indexOf(']');
    return lvstr.mid(1, endp-1).trimmed();
}

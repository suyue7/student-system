#include "scorepic.h"
#include "ui_scorepic.h"
#include "studentwidget.h"
#include <QtCharts>
#include <QString>
#include <QSqlQuery>

scorePic::scorePic(QWidget *parent,QString user) :
    QWidget(parent),
    ui(new Ui::scorePic)
{
    ui->setupUi(this);
    this->setWindowTitle("成绩分析");

    qDebug()<<user;
    QString sc=QString("SELECT * FROM score_table WHERE sid='%1'").arg(user);
    QSqlQuery query;
    query.exec(sc);
    int num1=0,num2=0,num3=0,num4=0,num5=0;
    while (query.next())
    {
        int sco=query.value("sscore").toInt();
        if (sco>=90&&sco<=100) num1++;
        else if (sco>=80&&sco<90) num2++;
        else if (sco>=70&&sco<80) num3++;
        else if (sco>=60&&sco<70) num4++;
        else if (sco>=0&&sco<60) num5++;
    }
    qDebug()<<num1<<num2<<num3<<num4<<num5;

    QChart *chart=new QChart();
    chart->setTitle("成绩分析饼状图"); //设置表格标题
    QPieSeries *series=new QPieSeries(chart);
    series->append("[90,100]",num1); //添加饼状图的各个部分（名称，数量）
    series->append("[80,90)",num2);
    series->append("[70,80)",num3);
    series->append("[60,70)",num4);
    series->append("[0,60)",num5);
    series->setPieSize(0.8);
    series->setHoleSize(0.25);//饼图中间空心的比例

    chart->setAnimationOptions(QChart::AllAnimations);
    chart->addSeries(series);
    QChartView *chartView;
    chartView=new QChartView(chart);
    ui->verticalLayout->insertWidget(0,chartView);
}

scorePic::~scorePic()
{
    delete ui;
}

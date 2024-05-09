#include "scorefinish.h"
#include "ui_scorefinish.h"
#include "scorepic.h"
#include "studentwidget.h"
#include <QtCharts>
#include <QString>
#include <QSqlQuery>

scoreFinish::scoreFinish(QWidget *parent,QString user) :
    QWidget(parent),
    ui(new Ui::scoreFinish)
{
    ui->setupUi(this);
    this->setWindowTitle("学分完成情况");

    QPixmap qp1("image/scorePic.png");
    ui->label->setPixmap(qp1);
    ui->label->setScaledContents(true);
    ui->label->show();

    int num1=0,num2=0,num3=0,num4=0;
    int score1=0,score2=0,score3=0,score4=0;
    QSqlQuery query,query1;
    QString les=QString("SELECT * FROM selectedlesson WHERE sid='%1'").arg(user);   //该同学选的课id
    query.exec(les);
    while (query.next())
    {
        qDebug()<<"进了第一个while";
        QString lesId=query.value("cid").toString();
        QString lt=QString("SELECT * FROM class_table WHERE cid='%1'").arg(lesId);   //对应id找
        qDebug()<<lt;
        query1.clear();
        query1.exec(lt);
        query1.first();
        QString type=query1.value("cclassify").toString();
        if (type=="公必") {num1++;score1+=query1.value("cscore").toInt();}
        else if (type=="公选") {num2++;score2+=query1.value("cscore").toInt();}
        else if (type=="专必") {num3++;score3+=query1.value("cscore").toInt();}
        else if (type=="专选") {num4++;score4+=query1.value("cscore").toInt();}
    }
    int sum=score1+score2+score3+score4;

    QChart *chart=new QChart();
    chart->setTitle("学分完成情况"); //设置表格标题
    QPieSeries *series=new QPieSeries(chart);
    series->append("已完成",sum); //添加饼状图的各个部分（名称，数量）
    series->append("未完成",160-sum);
    series->setPieSize(0.6);
    series->setHoleSize(0.25);//饼图中间空心的比例
    QPieSlice *slice=series->slices().at(1);
    slice->setColor(QColor(152,224,255));

    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->addSeries(series);
    QChartView *chartView;
    chartView=new QChartView(chart);
    ui->verticalLayout->insertWidget(0,chartView);

    ui->scoTable->setColumnCount(2);
    ui->scoTable->setHorizontalHeaderLabels(QStringList()<<"课程类别"<<"已修/总学分");
    ui->scoTable->setRowCount(4);
    ui->scoTable->verticalHeader()->hide();
    ui->scoTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->scoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->scoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->scoTable->setSelectionMode(QAbstractItemView::NoSelection);

    ui->scoTable->setItem(0,0,new QTableWidgetItem("公必"));
    ui->scoTable->setItem(1,0,new QTableWidgetItem("公选"));
    ui->scoTable->setItem(2,0,new QTableWidgetItem("专必"));
    ui->scoTable->setItem(3,0,new QTableWidgetItem("专选"));

    QString showGrade1=QString("%1 %2 %3").arg(QString::number(score1)).arg("/").arg("39");
    ui->scoTable->setItem(0,1,new QTableWidgetItem(showGrade1));
    QString showGrade2=QString("%1 %2 %3").arg(QString::number(score2)).arg("/").arg("8");
    ui->scoTable->setItem(1,1,new QTableWidgetItem(showGrade2));
    QString showGrade3=QString("%1 %2 %3").arg(QString::number(score3)).arg("/").arg("89");
    ui->scoTable->setItem(2,1,new QTableWidgetItem(showGrade3));
    QString showGrade4=QString("%1 %2 %3").arg(QString::number(score4)).arg("/").arg("24");
    ui->scoTable->setItem(3,1,new QTableWidgetItem(showGrade4));

    for (int i=0;i<4;i++)
        for (int j=0;j<2;j++)
            ui->scoTable->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    ui->label1->setText("当前已完成学分："+QString::number(sum));
    ui->label2->setText("毕业所需学分：160");


    QBarSet *set1=new QBarSet("已完成");
    QBarSet *set2=new QBarSet("未完成");
    *set1<<score1<<score2<<score3<<score4;
    *set2<<39<<8<<89<<24;
    QPercentBarSeries *series1=new QPercentBarSeries();
    series1->append(set1);
    series1->append(set2);
    QChart *chart1=new QChart();
    chart1->addSeries(series1);
    chart1->setAnimationOptions(QChart::SeriesAnimations);
    //坐标轴
    QStringList categories;
    categories<<"公必"<<"公选"<<"专必"<<"专选";
    QBarCategoryAxis *axis=new QBarCategoryAxis();
    axis->append(categories);
    chart1->createDefaultAxes();
    chart1->setAxisX(axis,series1);
    //图例
    chart1->legend()->setVisible(true);
    chart1->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView1=new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout->addWidget(chartView1,3,0);

}

scoreFinish::~scoreFinish()
{
    delete ui;
}

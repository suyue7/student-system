#include "accessgraphic.h"
#include "ui_accessgraphic.h"
#include "mainwindow.h"

AccessGraphic::AccessGraphic(QWidget * dg, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccessGraphic)
{
    ui->setupUi(this);

    dialog = (AccessBrowseDialog*)dg;
    QString lessid = dialog->getSelectedLessonId();
    QString sql = QString("SELECT cname FROM class_table WHERE cid='%1';").arg(lessid);
    QSqlQuery query;
    query.exec(sql);
    if(query.next())
        ui->lessonlabel->setText(QString("课程 [%1]%2 评教情况分析：").arg(lessid, query.value(0).toString()));
    sql = QString("SELECT tscore FROM selectedlesson WHERE is_assessed=1 AND selectedlesson.cid='%1';").arg(lessid);
    query.exec(sql);
    int sum = 0, cnt = 0;
    while(query.next()){
        sum += query.value(0).toInt();
        cnt ++;
    }
    double avg_score = (double)sum / cnt;
    QString str = QString::number(avg_score, 'f', 2);
    ui->scorelabel->setText(QString("平均得分：%1").arg(str));

    showGraphic(lessid);
}

AccessGraphic::~AccessGraphic()
{
    delete ui;
}

void AccessGraphic::showGraphic(QString cid){
    QString sql=QString("select sum(case when tscore between 90 and 100 then 1 else 0 end) as A, sum(case when tscore between 80 and 89 then 1 else 0 end) as B,sum(case when tscore between 70 and 79 then 1 else 0 end) as C,sum(case when tscore between 60 and 69 then 1 else 0 end) as D,sum(case when tscore<60 then 1 else 0 end) as E from selectedlesson WHERE cid = '%1'").arg(cid);
    double count_a = 0, count_b = 0, count_c=0, count_d=0, count_e=0;
    QSqlQuery query;
    query.exec(sql);
    while(query.next()){
        count_a = query.value("A").toInt();
        count_b = query.value("B").toInt();
        count_c = query.value("C").toInt();
        count_d = query.value("D").toInt();
        count_e = query.value("E").toInt();
    }

    QChart* chart = new QChart;
    chart->setTitle("评教情况分析图");

    QChartView* chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChart(chart);

    //加入到主界面中
    ui->verticalLayout->addWidget(chartView);

    //设置X轴
    QBarCategoryAxis* category_axis_x = new QBarCategoryAxis(chart);
    chart->addAxis(category_axis_x, Qt::AlignBottom);

    //设置X轴标签
    QStringList categories = { "A", "B", "C", "D", "E"};
    category_axis_x->setCategories(categories);

    //设置Y轴
    QValueAxis* axis_y = new QValueAxis(chart);
    chart->addAxis(axis_y, Qt::AlignLeft);

    //创建柱状图
    QBarSeries* bar_series = new QBarSeries(chart);
    chart->addSeries(bar_series);

    //加入坐标轴
    bar_series->attachAxis(category_axis_x);
    bar_series->attachAxis(axis_y);

    //创建1组柱状图
    QBarSet* set = new QBarSet("", chart);
    bar_series->append(set);

    //设置数据
    QList<qreal> list_data = {count_a,count_b,count_c,count_d,count_e};
    set->append(list_data);
    //qDebug() << count_a << count_b << count_c << count_d << count_e;

    //设置显示范围
    axis_y->setRange(0, 10);

    //设置Y轴刻度数
    axis_y->setTickCount(3);
}

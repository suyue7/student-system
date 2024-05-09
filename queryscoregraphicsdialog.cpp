#include "queryscoregraphicsdialog.h"
#include "ui_queryscoregraphicsdialog.h"
#include "mainwindow.h"

QueryScoreGraphicsDialog::QueryScoreGraphicsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryScoreGraphicsDialog)
{
    ui->setupUi(this);

    loadTeacherLesson();
    ui->tabWidget->clear();//清空选项卡
    ui->tabWidget->setTabsClosable(false);
    for(int i = 0; i < lessData.size(); i++)
        getOneLessonTab(lessData[i]);//在后面添加选项卡

    ui->tiplabel->setText(QString("（老师：%1）课程：").arg(MainWindow::sfName));
}

QueryScoreGraphicsDialog::~QueryScoreGraphicsDialog()
{
    delete ui;
}

void QueryScoreGraphicsDialog::loadTeacherLesson()
{   QString sql = QString("SELECT cid, cname, cscore, cclassify, kcfs FROM class_table WHERE tid='%1';").arg(MainWindow::sfID);
    lessData.clear();
    QSqlQuery rs;
    rs.exec(sql);
    while(rs.next()){
        QString no = rs.value("cid").toString().trimmed();
        QString name = rs.value("cname").toString();
        int chour = rs.value("cscore").toInt();
        QString type = rs.value("cclassify").toString();
        QString ksfs = rs.value("kcfs").toString();
        lessData.append(*(new QueryLesson(no, name, chour, type, ksfs)));
    }
}

void QueryScoreGraphicsDialog::getOneLessonTab(QueryLesson ql){
    QWidget *oneTab = new QWidget(ui->tabWidget);
    ui->tabWidget->addTab(oneTab, ql.cname);//在后面添加选项卡
    QString s = QString::number(ql.cscore);
    QLabel *lessInfo = new QLabel(QString("学分：%1，类型：%2，考试方式：%3").arg(s, ql.cclassify, ql.ksfs));
    QGridLayout *layout = new QGridLayout(oneTab);
    layout->addWidget(lessInfo, 0, 0);
    layout->setAlignment(lessInfo, Qt::AlignTop);

    showGraphic(ql, layout);
}

void QueryScoreGraphicsDialog::showGraphic(QueryLesson ql, QGridLayout *layout){
    QString cid = ql.cid.trimmed();
    QString sql=QString("select sum(case when sscore between 90 and 100 then 1 else 0 end) as A, sum(case when sscore between 80 and 89 then 1 else 0 end) as B,sum(case when sscore between 70 and 79 then 1 else 0 end) as C,sum(case when sscore between 60 and 69 then 1 else 0 end) as D,sum(case when sscore<60 then 1 else 0 end) as E from score_table WHERE cid = '%1'").arg(cid);
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

    // 创建 QPieSeries 对象
    QPieSeries *series = new QPieSeries();
    //connect(series, SIGNAL(clicked(QPieSlice*)), this, SLOT(onPieSeriesClicked(QPieSlice*)));

    //定义各扇形切片的颜色
    //static const QStringList list_pie_color = {"#6480D6","#A1DC85","#FFAD25","#FF7777","#84D1EF","#4CB383",};
    static const QStringList list_pie_color = {"#6480D6","#4CB383","#FFAD25","#FF7777","#84D1EF"};

    //设置数据
    QList<qreal> list_data = {count_a, count_b, count_c, count_d, count_e};
    QStringList label_data = {"优秀", "良好", "中等", "及格", "不及格"};

    //扇形,添加数据序列
    for (int i = 0; i < list_pie_color.size(); i++) {
        QPieSlice* pie_slice = new QPieSlice();
        if(list_data[i] == 0)
            pie_slice->setLabelVisible(false);
        pie_slice->setValue(list_data[i]);
        pie_slice->setLabel(label_data[i]);
        pie_slice->setColor(list_pie_color[i]);
        pie_slice->setLabelColor(list_pie_color[i]);
        pie_slice->setBorderColor(list_pie_color[i]);
        series->append(pie_slice);
    }

    // 创建 QChart 对象
    QChart *chart = new QChart();
    chart->setTitle("成绩分布饼图"); // 设置标题
    chart->addSeries(series); // 将 QPieSeries 添加到 QChart 中

    //创建 QChartView 对象显示图表
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing); // 抗锯齿
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //图例
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setBackgroundVisible(false);

    //加入到布局中
    layout->addWidget(chartView, 1, 0);
}

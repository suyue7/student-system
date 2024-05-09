#include "tpersonalinfo.h"
#include "ui_tpersonalinfo.h"
#include "mainwindow.h"
#include "editinfodialog.h"
#include "lessoninfo.h"

TPersonalInfo::TPersonalInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TPersonalInfo)
{
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    QStringList VStrList;
    VStrList.push_back(QString("姓名"));
    VStrList.push_back(QString("教工号"));
    VStrList.push_back(QString("性别"));
    VStrList.push_back(QString("职称"));
    VStrList.push_back(QString("院系"));
    VStrList.push_back(QString("电话"));
    VStrList.push_back(QString("邮箱"));
    VStrList.push_back(QString("家庭住址"));
    //设置行列数(只有列存在的前提下，才可以设置列标签)
    int VlabelCnt = VStrList.count();
    ui->tableWidget->setRowCount(VlabelCnt);
    ui->tableWidget->setColumnCount(1);
    //设置列标签
    ui->tableWidget->setVerticalHeaderLabels(VStrList);

    //表格充满布局
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->lesstableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->lesstableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(MainWindow::sfName));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem(MainWindow::sfID));
    QString sql = QString("SELECT tsex, tjobtitle, tphonenumber, temail, tdepartment, taddress FROM teacher_table WHERE tname='%1';").arg(MainWindow::sfName);
    QSqlQuery query;
    query.exec(sql);
    if(query.next()){
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(query.value("tsex").toString()));
        ui->tableWidget->setItem(0, 3, new QTableWidgetItem(query.value("tjobtitle").toString()));
        ui->tableWidget->setItem(0, 4, new QTableWidgetItem(query.value("tdepartment").toString()));
        ui->tableWidget->setItem(0, 5, new QTableWidgetItem(query.value("tphonenumber").toString()));
        ui->tableWidget->setItem(0, 6, new QTableWidgetItem(query.value("temail").toString()));
        ui->tableWidget->setItem(0, 7, new QTableWidgetItem(query.value("taddress").toString()));
    }
    sql = QString("SELECT cid, cname FROM class_table WHERE tid='%1';").arg(MainWindow::sfID);
    query.exec(sql);
    QStringList lessonlist;
    while(query.next()){
        lessonlist.append(QString("[%1]%2").arg(query.value("cid").toString(), query.value("cname").toString()));
        ui->lesstableWidget->insertRow(ui->tableWidget->rowCount());
        //ui->lesstableWidget->setItem(0, ui->tableWidget->rowCount()-1, new QTableWidgetItem(temp));
    }
    int lesscnt = lessonlist.count();
    ui->lesstableWidget->setRowCount(lesscnt);
    ui->lesstableWidget->setColumnCount(1);
    for(int i = 0; i < lesscnt; i++){
        ui->lesstableWidget->setItem(0, i, new QTableWidgetItem(lessonlist[i]));
    }
}

TPersonalInfo::~TPersonalInfo()
{
    delete ui;
}

void TPersonalInfo::on_editButton_clicked()
{
    EditInfoDialog *edit = new EditInfoDialog(this);
    edit->show();
}


void TPersonalInfo::on_lesstableWidget_cellDoubleClicked(int row, int column)
{
    LessonInfo *li = new LessonInfo(ui->lesstableWidget->item(row, column)->data(Qt::DisplayRole).toString());
    li->show();
}


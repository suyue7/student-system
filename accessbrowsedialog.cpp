#include "accessbrowsedialog.h"
#include "ui_accessbrowsedialog.h"
#include "mainwindow.h"
#include "accessgraphic.h"

AccessBrowseDialog::AccessBrowseDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccessBrowseDialog)
{
    ui->setupUi(this);

    loadTeacherLesson();

    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->comboBox->addItems(lessData);
    ui->comboBox->setEditable(false);

    updateTable(ui->comboBox->currentText());
}

AccessBrowseDialog::~AccessBrowseDialog()
{
    delete ui;
}

void AccessBrowseDialog::loadTeacherLesson(){
    QString sql = QString("SELECT cid, cname FROM class_table WHERE tid='%1';").arg(MainWindow::sfID);
    QSqlQuery lesson;
    lesson.exec(sql);
    while(lesson.next()){
        QString no = lesson.value("cid").toString();
        QString name = lesson.value("cname").toString();
        lessData.append(QString("[%1] %2").arg(no, name));
    }
}

QString AccessBrowseDialog::getLessonId(QString lvstr){
    int endp = lvstr.indexOf(']');
    return lvstr.mid(1, endp-1).trimmed();
}

void AccessBrowseDialog::on_graphicpushButton_clicked()
{
    AccessGraphic * ac = new AccessGraphic(this);
    ac->show();
}

QString AccessBrowseDialog::getSelectedLessonId(){
    return selectedLessonID;
}

void AccessBrowseDialog::updateTable(QString text){
    ui->tableWidget->clear();

    /*设置列字段名（两种方式）*/
    QStringList HStrList;
    HStrList.push_back(QString("评分"));
    HStrList.push_back(QString("评语"));
    //设置行列数(只有列存在的前提下，才可以设置列标签)
    int HlabelCnt = HStrList.count();
    ui->tableWidget->setColumnCount(HlabelCnt);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,350);
    //设置列标签
    ui->tableWidget->setHorizontalHeaderLabels(HStrList);

    selectedLessonID = getLessonId(text);

    QString sql = QString("SELECT tscore, comment FROM selectedlesson WHERE cid='%1';").arg(selectedLessonID);
    QSqlQuery query;
    query.exec(sql);
    int i = 0;
    while(query.next()){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(query.value("tscore").toString()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(query.value("comment").toString()));
        i++;
    }
}

void AccessBrowseDialog::on_comboBox_textActivated(const QString &arg1)
{
    updateTable(ui->comboBox->currentText());
}

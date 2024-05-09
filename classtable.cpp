#include "classtable.h"
#include "ui_classtable.h"
#include <QSqlQuery>
#include <QFileDialog>
#include <QFile>
#include <QTextEdit>
#include <QMessageBox>

ClassTable::ClassTable(QWidget *parent,QString user) :
    QWidget(parent),
    ui(new Ui::ClassTable)
{
    ui->setupUi(this);
    this->setWindowTitle("查看课表");

    ui->export_2->setIcon(QIcon("image/file.png"));
    ui->export_2->setLayoutDirection(Qt::LeftToRight);

    ui->classtb->setColumnCount(7);
    for (int i=0;i<7;i++)
        ui->classtb->setColumnWidth(i,90);
    ui->classtb->setRowCount(9);
    for (int i=0;i<9;i++)
        ui->classtb->setRowHeight(i,60);
    ui->classtb->setRowHeight(9,63);
    ui->classtb->setHorizontalHeaderLabels(QStringList()<<"周日"<<"周一"<<"周二"<<"周三"<<"周四"<<"周五"<<"周六");
    ui->classtb->setVerticalHeaderLabels(QStringList()<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9");
    ui->classtb->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->classtb->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->classtb->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->classtb->setSelectionMode(QAbstractItemView::NoSelection);

    QSqlQuery query,query1,query2;
    QString sql=QString("SELECT cid FROM selectedlesson WHERE sid='%1'").arg(user);
    query.exec(sql);
    while (query.next())
    {
        QString thisId=query.value("cid").toString();
        sql=QString("SELECT * FROM arr_table WHERE cid='%1'").arg(thisId);
        query1.clear();
        query1.exec(sql);

        query2.clear();
        sql=QString("SELECT * FROM class_table WHERE cid='%1'").arg(thisId);  //找课程名称
        query2.exec(sql);
        query2.first();
        QString thisName=query2.value("cname").toString();

        while (query1.next())
        {
            int classDay=query1.value("weekday").toInt();
            int classTime=query1.value("classtime").toInt();
            if (classDay==7) classDay=0;

            QString info=QString("%1\n%2").arg(thisName).arg(query1.value("clocation").toString());
            ui->classtb->setItem(classTime-1,classDay,new QTableWidgetItem(info));
            ui->classtb->item(classTime-1,classDay)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->classtb->item(classTime-1,classDay)->setBackground(Qt::lightGray);
        }
    }
}

ClassTable::~ClassTable()
{
    delete ui;
}

void ClassTable::on_export_2_clicked()
{
    QString filepath=QFileDialog::getSaveFileName(this,tr("Save as..."),QString(),tr("EXCEL files (*.xls *.xlsx)"));

    QFile file(filepath);
    if (!file.open(QFile::WriteOnly|QIODevice::Text)) return;
    int row=ui->classtb->rowCount();
    int col=ui->classtb->columnCount();
    QList<QString> list;

    //添加列标题
    QString HeaderRow;
    HeaderRow.append("\t");
    for (int i=0;i<col;i++)
        HeaderRow.append(ui->classtb->horizontalHeaderItem(i)->text()+"\t");

    list.push_back(HeaderRow);
    for (int i=0;i<row;i++)
    {
        QString rowStr="";
        rowStr.append(ui->classtb->verticalHeaderItem(i)->text());
        rowStr.append("\t");
        for (int j=0;j<col;j++)
        {
            if (ui->classtb->item(i,j)==NULL) rowStr.append("\t");
            else
            {
                QString s,q,h;
                s=ui->classtb->item(i,j)->text();
                int k=s.indexOf('\n');
                q=s.mid(0,k);
                h=s.mid(k+1,s.length());
                rowStr.append(q+" "+h+"\t");
            }
        }
        list.push_back(rowStr);
    }
    //将表格内容添加到富文本中
    QTextEdit textEdit;
    for (int i=0;i<list.size();i++)
        textEdit.append(list.at(i));
    //写入文件中
    QTextStream ts(&file);
    ts<<textEdit.document()->toPlainText();
    file.close();

    QMessageBox::information(this,"温馨提示","导出成功！");
}


#include "news_ope_teacher.h"
#include "ui_news_ope_teacher.h"
#include "mainwindow.h"
news_ope_teacher::news_ope_teacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::news_ope_teacher)
{
    ui->setupUi(this);

}

news_ope_teacher::~news_ope_teacher()
{
    delete ui;
}

void news_ope_teacher::on_exitBtn_clicked()
{
    close();
}


void news_ope_teacher::on_collectBtn_clicked()
{
    QString title=this->ui->titlelabel->text();
    QString sql = QString("SELECT news_id FROM news_table WHERE news_title = '%1'").arg(title);

    QSqlQuery query;
    query.exec(sql);
    if(query.next()){
        QSqlQuery test;
        test.exec(QString("SELECT * FROM like_table WHERE news_id = '%1' AND per_id = '%2';").arg(query.value(0).toString(), MainWindow::sfID));
        if(test.next())
            return;
        sql = QString("INSERT INTO like_table(news_id, per_id) VALUES('%1', '%2');").arg(query.value(0).toString(), MainWindow::sfID);
        test.exec(sql);
        qDebug() << sql;
    }
}


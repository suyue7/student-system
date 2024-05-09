#include "widget.h"
#include "ui_widget.h"
#include "DBOperator.h"
#include <QtSql/QSqlDatabase>
#include <QStringList>
#include <QtSql/QSqlQuery>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

}

Widget::~Widget()
{
    dbp.DBClose();
    delete ui;
}


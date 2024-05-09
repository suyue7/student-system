#include "helpwidget.h"
#include "ui_helpwidget.h"

helpwidget::helpwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::helpwidget)
{
    ui->setupUi(this);
}

helpwidget::~helpwidget()
{
    delete ui;
}

void helpwidget::on_exitBtn_clicked()
{
    close();
}


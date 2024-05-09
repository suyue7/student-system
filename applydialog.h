#ifndef APPLYDIALOG_H
#define APPLYDIALOG_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStringListModel>
#include <QCompleter>
#include <regex>
#include "mainwindow.h"

namespace Ui {
class ApplyDialog;
}

class ApplyDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ApplyDialog(QWidget *parent = nullptr);
    ~ApplyDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ApplyDialog *ui;
};

#endif // APPLYDIALOG_H

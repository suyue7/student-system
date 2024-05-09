#ifndef EDITINFODIALOG_H
#define EDITINFODIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <regex>
#include<QStringListModel>
#include <QCompleter>
#include "tpersonalinfo.h"

namespace Ui {
class EditInfoDialog;
}

class EditInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditInfoDialog(QWidget * info, QWidget *parent = nullptr);
    ~EditInfoDialog();
    bool getChangeflag();

private slots:
    void on_cancelButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::EditInfoDialog *ui;
    TPersonalInfo * infowidget;
    bool changeflag;
};

#endif // EDITINFODIALOG_H

#ifndef TPERSONALINFO_H
#define TPERSONALINFO_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class TPersonalInfo;
}

class TPersonalInfo : public QWidget
{
    Q_OBJECT

public:
    Ui::TPersonalInfo *ui;    //方便在编辑信息窗口修改信息
    explicit TPersonalInfo(QWidget *parent = nullptr);
    ~TPersonalInfo();

private slots:
    void on_editButton_clicked();

//private:
//    Ui::TPersonalInfo *ui;
    void on_lesstableWidget_cellDoubleClicked(int row, int column);
};

#endif // TPERSONALINFO_H

#ifndef TEACHERPAGE_H
#define TEACHERPAGE_H
#include"dboperator.h"
#include"mainpage2.h"
#include <QWidget>
#include<QStandardItemModel>
#include<QAbstractItemView>
#include<QMessageBox>
#include<QSqlQueryModel>
#include<QSqlDatabase>
#include<QObject>
#include<QTableView>
#include<QApplication>
#include<QSqlRecord>
#include<QItemSelectionModel>
namespace Ui {
class teacherpage;
}

class teacherpage : public QWidget
{
    Q_OBJECT

public:
    explicit teacherpage(QWidget *parent = nullptr);
    ~teacherpage();
    DBOperator myDataBase;
    //设置表格样式
    void setTabletInfo();
    //获取表格信息
    void getDatabaseInfo();
    //表格组件模式
    QStandardItemModel *dataTableModel;
     QItemSelectionModel *selection;
    QStringList listData;

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_deleteBtn_clicked();

    void on_refreshBtn_clicked();

    void on_toclassBtn_clicked();

    void on_tostudentBtn_clicked();

    void on_toannouncBtn_clicked();

    void on_searchBtn_clicked();

    void on_pushButton_clicked();

    void on_quitBtn_clicked();

    void on_teacherTable_clicked(const QModelIndex &index);

private:
    Ui::teacherpage *ui;
};

#endif // TEACHERPAGE_H

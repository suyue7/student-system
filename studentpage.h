#ifndef STUDENTPAGE_H
#define STUDENTPAGE_H
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
#include<QStringList>
#include<QApplication>
#include<QSqlRecord>
//#include<QRegExp>
#include<QItemSelectionModel>
#include<regex>
namespace Ui {
class studentpage;
}

class studentpage : public QWidget
{
    Q_OBJECT

public:
    explicit studentpage(QWidget *parent = nullptr);
    ~studentpage();
    DBOperator myDataBase;
    //设置表格样式
    void setTabletInfo();
    //获取表格信息
    void getDatabaseInfo();
    void shownew();
    //表格组件模式
    QStandardItemModel *dataTableModel;
     QItemSelectionModel *selection;
    QStandardItemModel *scoreTableModel;
     QStringList  listData;
private slots:
    void on_toclassBtn_clicked();

    void on_toteacherBtn_clicked();

    void on_toanounceBtn_clicked();

    void on_searchBtn_clicked();

    void on_studentTable_clicked(const QModelIndex &index);

    void on_deleterow_clicked();

    void on_refreshBtn_clicked();

    void on_confirmBtn_clicked();

    void on_deleteBtn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void on_scoreBtn_clicked();
    void on_quitBtn_clicked();

private:
    Ui::studentpage *ui;
};

#endif // STUDENTPAGE_H

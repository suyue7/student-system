#ifndef MAINPAGE2_H
#define MAINPAGE2_H
#include "dboperator.h"
#include "studentpage.h"
#include "teacherpage.h"
#include "announcepage.h"
#include "scoreinputdialog.h"
#include <QWidget>
#include<QStandardItemModel>
#include<QAbstractItemView>
#include<QMessageBox>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QObject>
#include<QTableView>
#include<QApplication>
#include<QSqlRecord>
#include<QItemSelectionModel>
#include<QFileDialog>
#include<QFile>
//#include<QTextCodec>
#include<QTextStream>
#include<QLocale>
#include<QCompleter>
#include"scoreinputdialog.h"
namespace Ui {
class mainpage2;
}

class mainpage2 : public QWidget
{
    Q_OBJECT

public:
    explicit mainpage2(QWidget *parent = nullptr);
    ~mainpage2();
    //连接数据库对象
    DBOperator myDataBase;
    //设置表格样式
    void setTabletInfo();
    //获取表格信息
    void getDatabaseInfo();
    void shownew();
    //表格组件模式
    QStandardItemModel *dataTableModel;
    QItemSelectionModel *selection;
    ScoreInputDialog *scoreinput;
    QStringList listData;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_refreshBtn_clicked();

    void on_deleteBtn_clicked();

    void on_searchBtn_clicked();

    void on_tostudentBtn_clicked();

    void on_toteacherBtn_clicked();

    void on_toannouceBtn_clicked();

    void on_classTable_clicked(const QModelIndex &index);

    void on_confirmBtn_clicked();

    void on_deleterow_clicked();

    void on_excelBtn_clicked();

    void on_scorelogBtn_clicked();

    void on_yesBtn_clicked();

    void on_startBtn_clicked();

    void on_quitBtn_clicked();

    void gets();

private:
    Ui::mainpage2 *ui;
};

#endif // MAINPAGE2_H

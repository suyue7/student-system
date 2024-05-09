#ifndef ANNOUNCEPAGE_TEACHER_H
#define ANNOUNCEPAGE_TEACHER_H
//#include "dboperator.h"
//#include"mainpage2.h"
#include "mainwindow.h"
#include"news_ope_teacher.h"
#include"ui_news_ope_teacher.h"
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
#include<QStringListModel>
#include<QTime>
#include<QListView>
#include<QStringListModel>
#include<QSqlQuery>
namespace Ui {
class announcepage_teacher;
}

class announcepage_teacher : public QWidget
{
    Q_OBJECT

public:
    explicit announcepage_teacher(QWidget *parent = nullptr);
    ~announcepage_teacher();
    //DBOperator myDataBase;
    QStandardItemModel *dataTableModel;
    QItemSelectionModel *selection;
    QStringListModel *m1;
    void setlistinfo();

protected slots:
    void gets();
    void shownew();

    void on_tabWidget_currentChanged(int index);

    void on_searchBtn_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);


private slots:
    void on_exitBtn_clicked();

    void on_FavoritesBtn_clicked();

private:
    Ui::announcepage_teacher *ui;
};

#endif // ANNOUNCEPAGE_TEACHER_H

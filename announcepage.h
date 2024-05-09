#ifndef ANNOUNCEPAGE_H
#define ANNOUNCEPAGE_H
#include "dboperator.h"
#include"mainpage2.h"
#include"news_ope.h"
#include"ui_news_ope.h"
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

namespace Ui {
class announcepage;
}

class announcepage : public QWidget
{
    Q_OBJECT

public:
    explicit announcepage(QWidget *parent = nullptr);
    ~announcepage();
    DBOperator myDataBase;
    QStandardItemModel *dataTableModel;
     QItemSelectionModel *selection;
    QStringListModel *m1;
    void setlistinfo();
    QStringList listData;
protected slots:
    void gets();
    void shownew();
    void on_toclassBtn_clicked();

    void on_tostudentBtn_clicked();

    void on_toteacherBtn_clicked();

    void on_deleteBtn_clicked();

    void on_tabWidget_currentChanged(int index);



    void on_publishBtn_clicked();

    void on_searchBtn_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);


private:
    Ui::announcepage *ui;
};

#endif // ANNOUNCEPAGE_H

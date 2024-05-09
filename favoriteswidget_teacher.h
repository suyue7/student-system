#ifndef FAVORITESWIDGET_TEACHER_H
#define FAVORITESWIDGET_TEACHER_H

#include "news_ope_teacher.h"
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
#include<QCompleter>
#include<QList>
#include<vector>
using namespace std;

namespace Ui {
class FavoritesWidget_teacher;
}

class FavoritesWidget_teacher : public QWidget
{
    Q_OBJECT

public:
    explicit FavoritesWidget_teacher(QWidget *parent = nullptr);
    ~FavoritesWidget_teacher();
    QStandardItemModel *dataTableModel;
    QItemSelectionModel *selection;
    QStringListModel *m1;
    void setlistinfo();
    struct news{
        QString id;
        QString classify;
        QString content;
        QString time;
        QString where;
        QString title;
        news(QString i, QString cla, QString con, QString t, QString w, QString tit){
            id = i;
            classify = cla;
            content = con;
            time = t;
            where = w;
            title = tit;
        }
    };

protected slots:
    void gets();
    void shownew();
    void on_tabWidget_currentChanged(int index);
    void on_searchBtn_clicked();
    void on_listView_doubleClicked(const QModelIndex &index);

private slots:
    void on_exitButton_clicked();

    void on_dropButton_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::FavoritesWidget_teacher *ui;
    QStringList newsid;
    QList<news*> newsinfo;
    QStringList title;
    QStringList droplist;
};

#endif // FAVORITESWIDGET_TEACHER_H

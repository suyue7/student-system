#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QScreen>
#include "scoreinputdialog_teacher.h"
#include "queryscoregraphicsdialog.h"
#include "ui_mainwindow.h"
#include "tpersonalinfo.h"
#include "accessbrowsedialog.h"
#include "announcepage_teacher.h"
#include "applydialog.h"
#include "changepasswd.h"
#include "helpwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static int sfLB;
    static QString sfID;
    static QString sfName;
    static bool dbflag;
    static void connectdb(QSqlDatabase& db);

private slots:
    void on_scoreinputpushButton_clicked();

    void on_pushButton_clicked();

    void on_infopushButton_clicked();

    void on_assessbrowsepushButton_clicked();

    void on_announcementpushButton_clicked();

    void on_exitButton_clicked();

    void on_applyButton_clicked();

    void on_changepwBtn_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H

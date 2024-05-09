#ifndef SCOREINPUTDIALOG_H
#define SCOREINPUTDIALOG_H
#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStandardItemModel>
#include <QModelIndex>
#include <regex>

namespace Ui {
class ScoreInputDialog;
}

class ScoreInputDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreInputDialog(QWidget *parent = nullptr);
    ~ScoreInputDialog();
    QString selectedLessonID;
    void setmodel();

private slots:
    void on_browseradioButton_clicked();
    void on_exitpushButton_clicked();

private:
    Ui::ScoreInputDialog *ui;
    QStandardItemModel* model;

    bool inputFlag = false;
    void loadLessonScore();
    bool updateLessonScore();
    QString getLessonId(QString lvstr);
};



#endif // SCOREINPUTDIALOG_H

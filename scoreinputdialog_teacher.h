#ifndef SCOREINPUTDIALOG_TEACHER_H
#define SCOREINPUTDIALOG_TEACHER_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStandardItemModel>
#include <QFile>
#include <QFileDialog>
#include <QModelIndex>
#include <QTextEdit>
#include <regex>

namespace Ui {
class ScoreInputDialog_teacher;
}

class ScoreInputDialog_teacher : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreInputDialog_teacher(QWidget *parent = nullptr);
    ~ScoreInputDialog_teacher();

private slots:
    void on_browseradioButton_clicked();
    void on_comboBox_activated();

    void on_exitpushButton_clicked();

    void on_exportpushButton_clicked();

private:
    Ui::ScoreInputDialog_teacher *ui;
    QStandardItemModel* model;
    QString selectedLessonID = "";
    bool inputFlag = false;
    QStringList lessData;
    void loadTeacherLesson();
    void loadLessonScore();
    bool updateLessonScore();
    QString getLessonId(QString lvstr);
};



#endif // SCOREINPUTDIALOG_TEACHER_H

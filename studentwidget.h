#ifndef STUDENTWIDGET_H
#define STUDENTWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class StudentWidget;
}

class StudentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudentWidget(QWidget *parent = nullptr,QString user="");
    ~StudentWidget();

private slots:

    void on_selectLesson_clicked();

    void on_editInfo_clicked();

    void on_cancelLesson_clicked();

    void on_checkBtn_clicked();

    //void on_checkLesson_2_clicked();

    void on_assessSub_clicked();

    void on_checkPic_clicked();

    void on_checkFinish_clicked();

    void on_newsBtn_clicked();

    void on_checkClass_clicked();

    void on_exportScore_clicked();

    void on_quitBtn_clicked();

    void on_assessbox_activated(int index);

    void on_helpBtn_clicked();

private:
    Ui::StudentWidget *ui;
    int lessonNum=0;
    QString user;
    int selNum=0;
    QSqlQueryModel* model;
};

#endif // STUDENTWIDGET_H

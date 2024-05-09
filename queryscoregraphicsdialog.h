#ifndef QUERYSCOREGRAPHICSDIALOG_H
#define QUERYSCOREGRAPHICSDIALOG_H

#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QGridLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

namespace Ui {
class QueryScoreGraphicsDialog;
}

class QueryScoreGraphicsDialog : public QWidget
{
    Q_OBJECT

public:
    explicit QueryScoreGraphicsDialog(QWidget *parent = nullptr);
    ~QueryScoreGraphicsDialog();
    class QueryLesson{
    public:
        QString cid;
        QString cname;
        int cscore;
        QString cclassify;
        QString ksfs;

        QueryLesson(QString uUid, QString uName, int uChour, QString uType, QString uKsfs)
        {   this->cid = uUid;
            this->cname = uName;
            this->cscore = uChour;
            this->cclassify = uType;
            this->ksfs = uKsfs;
        }
    };

private:
    Ui::QueryScoreGraphicsDialog *ui;
    QList<QueryLesson> lessData;
    void loadTeacherLesson();
    void getOneLessonTab(QueryLesson ql);
    void showGraphic(QueryLesson ql, QGridLayout *layout);
};

#endif // QUERYSCOREGRAPHICSDIALOG_H

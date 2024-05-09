#ifndef NEWS_OPE_TEACHER_H
#define NEWS_OPE_TEACHER_H
#include"announcepage_teacher.h"
#include <QWidget>

namespace Ui {
class news_ope_teacher;
}

class news_ope_teacher : public QWidget
{
    Q_OBJECT

public:
    explicit news_ope_teacher(QWidget *parent = nullptr);
    ~news_ope_teacher();
    QString ope_name;
    Ui::news_ope_teacher *ui;
//signals:void closed();
//public  slots:
//    void on_refreshBtn_clicked();
private slots:
    void on_exitBtn_clicked();

    void on_collectBtn_clicked();

private:

};

#endif // NEWS_OPE_TEACHER_H

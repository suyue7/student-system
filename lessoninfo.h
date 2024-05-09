#ifndef LESSONINFO_H
#define LESSONINFO_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class LessonInfo;
}

class LessonInfo : public QWidget
{
    Q_OBJECT

public:
    explicit LessonInfo(QString lessID, QWidget *parent = nullptr);
    ~LessonInfo();

private:
    Ui::LessonInfo *ui;
    QString lessID;
    void setContent();
    QString getLessonId(QString lvstr);
};

#endif // LESSONINFO_H

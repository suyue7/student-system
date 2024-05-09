#ifndef NEWS_OPE_H
#define NEWS_OPE_H
#include"announcepage.h"
#include <QWidget>
#include<QCompleter>
#include"mainpage2.h"
namespace Ui {
class news_ope;
}

class news_ope : public QWidget
{
    Q_OBJECT

public:
    explicit news_ope(QWidget *parent = nullptr);
    ~news_ope();
    QString ope_name;
    Ui::news_ope *ui;
    QStringList listData;
signals:void closed();
public  slots:
    void on_refreshBtn_clicked();
private:

};

#endif // NEWS_OPE_H

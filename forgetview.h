#ifndef FORGETVIEW_H
#define FORGETVIEW_H
#include"dboperator.h"
#include <QWidget>
#include"mainpage2.h"
#include<sign_page.h>
namespace Ui {
class Forgetview;
}

class Forgetview : public QWidget
{
    Q_OBJECT

public:
    explicit Forgetview(QWidget *parent = nullptr);
    ~Forgetview();
     DBOperator myDataBase;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Forgetview *ui;
};

#endif // FORGETVIEW_H

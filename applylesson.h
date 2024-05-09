#ifndef APPLYLESSON_H
#define APPLYLESSON_H

#include <QWidget>

namespace Ui {
class applylesson;
}

class applylesson : public QWidget
{
    Q_OBJECT

public:
    explicit applylesson(QWidget *parent = nullptr,QString cid="");
    ~applylesson();
signals:
    void closed();

private slots:
    void on_subBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::applylesson *ui;
    QString cid;
};

#endif // APPLYLESSON_H

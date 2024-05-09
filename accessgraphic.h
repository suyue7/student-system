#ifndef ACCESSGRAPHIC_H
#define ACCESSGRAPHIC_H

#include "accessbrowsedialog.h"
#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QtCharts>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QVBoxLayout>

namespace Ui {
class AccessGraphic;
}

class AccessGraphic : public QWidget
{
    Q_OBJECT

public:
    explicit AccessGraphic(QWidget * dg, QWidget *parent = nullptr);
    ~AccessGraphic();
    void showGraphic(QString cid);

private:
    Ui::AccessGraphic *ui;
    AccessBrowseDialog * dialog;
};

#endif // ACCESSGRAPHIC_H

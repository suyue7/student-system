#ifndef CLASSTABLE_H
#define CLASSTABLE_H

#include <QWidget>

namespace Ui {
class ClassTable;
}

class ClassTable : public QWidget
{
    Q_OBJECT

public:
    explicit ClassTable(QWidget *parent = nullptr,QString user="");
    ~ClassTable();

private slots:
    void on_export_2_clicked();

private:
    Ui::ClassTable *ui;
};

#endif // CLASSTABLE_H

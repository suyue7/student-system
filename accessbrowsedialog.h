#ifndef ACCESSBROWSEDIALOG_H
#define ACCESSBROWSEDIALOG_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class AccessBrowseDialog;
}

class AccessBrowseDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AccessBrowseDialog(QWidget *parent = nullptr);
    ~AccessBrowseDialog();
    QString getSelectedLessonId();

private slots:
    void on_graphicpushButton_clicked();

    void on_comboBox_textActivated(const QString &arg1);

private:
    Ui::AccessBrowseDialog *ui;
    QStringList lessData;
    QString selectedLessonID = "";
    QString getLessonId(QString lvstr);
    void loadTeacherLesson();
    void updateTable(QString text);
};

#endif // ACCESSBROWSEDIALOG_H

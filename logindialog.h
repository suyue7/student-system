#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QWidget>
#include <QButtonGroup>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSettings>
#include"mainpage2.h"
#include"studentwidget.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QWidget
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    //设置鼠标按下可移动窗口的区域，在子窗口中必须设置该区域
    void setAreaMovable(const QRect rt);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_loginpushButton_clicked();

    void on_exitpushButton_clicked();

    void on_checkBox_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::LoginDialog *ui;
    QButtonGroup *IdentityGroup;
    QSqlDatabase db;
    bool ispassword;
    QRect m_areaMovable;//可移动窗口的区域，鼠标只有在该区域按下才能移动窗口
    bool m_bPressed;//鼠标按下标志（不分左右键）
    QPoint m_ptPress;//鼠标按下的初始位置
};

#endif // LOGINDIALOG_H

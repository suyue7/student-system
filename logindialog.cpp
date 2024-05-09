#include "logindialog.h"
#include "ui_logindialog.h"
#include "DatabaseConection.h"
#include "mainwindow.h"
#include "scoreinputdialog_teacher.h"

#define CONFIGPATH (QCoreApplication::applicationDirPath() + "/config/config.ini")

LoginDialog::LoginDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connectdb(db); //连接数据库

    //检测连接是否成功
    if(db.open()){
        //QMessageBox::information(this, "连接提示", "连接成功");
    }else{
        QMessageBox::warning(this, "连接提示", "连接失败");
    }

    this->setWindowFlags(Qt::FramelessWindowHint);
    m_areaMovable = this->geometry();
    m_bPressed = false;


    //建立单选框组
    IdentityGroup = new QButtonGroup(this);
    IdentityGroup->addButton(ui->studentradioButton, 0);
    IdentityGroup->addButton(ui->teacherradioButton, 1);
    IdentityGroup->addButton(ui->adminradioButton, 2);

    ui->uidlineEdit->setPlaceholderText("请输入原密码");
    ui->passwordlineEdit->setPlaceholderText("请输入原密码");
    ui->passwordlineEdit->setEchoMode(QLineEdit::Password);//以黑点显示

    QSettings setting(CONFIGPATH, QSettings::IniFormat); // 打开存放登录信息的ini文件
    QString isremember = setting.value("login/isremember").toString(); // 是否选择了记住密码
    QString name = QString::fromUtf8(setting.value("login/username").toByteArray()); // 账号
    QString lock = setting.value("login/password").toString(); // 密码
    int sf = setting.value("login/sflb").toInt(); //身份
    ui->uidlineEdit->setText(name); // 显示上一次登录的账号名
    if (isremember == "true") // 记住密码
    {
        ui->uidlineEdit->setText(name);
        ui->passwordlineEdit->setText(lock); // 密码写在密码输入框
        if(sf == 0){
            ui->studentradioButton->setChecked(true);
        }else if(sf == 1){
            ui->teacherradioButton->setChecked(true);
        }else if(sf == 2){
            ui->adminradioButton->setChecked(true);
        }
        ui->checkBox->setChecked(true); // 记住密码那里打√
        ispassword = true; // 记住密码
    }
    else
    {
        ui->checkBox->setChecked(false); // 记住密码那里不打√
        ispassword = false; // 不记住密码
    }
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginpushButton_clicked()
{
    int sflb = 0;
    QString sfStr = "", tbName = "";
    //获取用户名和密码
    QString password = ui->passwordlineEdit->text().trimmed();
    QString uid = ui->uidlineEdit->text().trimmed();
    if(uid.length() == 0){
        QMessageBox::warning(this, "登录提示", "请输入用户名！");
        return;
    }
    if(password.length() == 0){
        QMessageBox::warning(this, "登录提示", "请输入密码！");
        return;
    }
    //确定登录者身份
    if(ui->studentradioButton->isChecked()){
        sflb = 0; sfStr = "学号：";
        tbName = "student";
        QString sql = QString("select * from student_table where sid = '%1';").arg(uid);
        QSqlQuery query;
        query.exec(sql);
        if(query.next()) {
            QString pwStr = query.value("spasswd").toString();
            QString nameStr = query.value("sname").toString().trimmed();
            if(pwStr=="" || pwStr == password){
                MainWindow::sfLB = sflb;
                MainWindow::sfID = uid;
                MainWindow::sfName = nameStr;
                qDebug() << query.value("sname").toString() ;

                QSettings writeini(CONFIGPATH, QSettings::IniFormat); // 打开ini文件
                if (ispassword) // 选择保存密码
                {
                    writeini.setValue("login/isremember", "true"); // 写ini文件时记录为true
                }
                else // 不保存密码
                {
                    writeini.setValue("login/isremember", "false"); // 写ini文件时记录为false
                }
                writeini.setValue("login/username", uid); // 把账号写入ini文件
                writeini.setValue("login/password", password); // 把密码写入ini文件
                writeini.setValue("login/sflb", sflb); // 把身份写入ini文件


                StudentWidget *sw=new StudentWidget(NULL,uid);
                sw->show();


                close();
            }else
                QMessageBox::warning(this, "登录提示", "密码不正确， 请重新输入！");
        }else
            QMessageBox::warning(this, "登录提示", sfStr+"《"+uid+"》不存在， 请重新输入！");
    }else if(ui->teacherradioButton->isChecked()){
        sflb = 1; sfStr = "教师号：";
        tbName = "teacher";
        QString sql = QString("select * from teacher_table where tid = '%1';").arg(uid);
        QSqlQuery query;
        query.exec(sql);
        if(query.next()) {
            QString pwStr = query.value("tpasswd").toString();
            QString nameStr = query.value("tname").toString().trimmed();
            if(pwStr=="" || pwStr == password){
                MainWindow::sfLB = sflb;
                MainWindow::sfID = uid;
                MainWindow::sfName = nameStr;

                QSettings writeini(CONFIGPATH, QSettings::IniFormat); // 打开ini文件
                if (ispassword) // 选择保存密码
                {
                    writeini.setValue("login/isremember", "true"); // 写ini文件时记录为true
                }
                else // 不保存密码
                {
                    writeini.setValue("login/isremember", "false"); // 写ini文件时记录为false
                }
                writeini.setValue("login/username", uid); // 把账号写入ini文件
                writeini.setValue("login/password", password); // 把密码写入ini文件
                writeini.setValue("login/sflb", sflb); // 把身份写入ini文件

                //qDebug() << query.value("tname").toString() ;
                MainWindow* w = new MainWindow();
                w->show();
                close();
            }else
                QMessageBox::warning(this, "登录提示", "密码不正确， 请重新输入！");
        }else
            QMessageBox::warning(this, "登录提示", sfStr+"《"+uid+"》不存在， 请重新输入！");
    }else if(ui->adminradioButton->isChecked()){
        sflb = 2; sfStr = "教务号：";
        tbName = "admin";
        QString sql = QString("select * from admin_table where admin_id = '%1';").arg(uid);
        QSqlQuery query;
        query.exec(sql);
        if(query.next()) {
            QString pwStr = query.value("admin_passwd").toString();
            QString nameStr = query.value("admin_name").toString().trimmed();
            if(pwStr=="" || pwStr == password){
                MainWindow::sfLB = sflb;
                MainWindow::sfID = uid;
                MainWindow::sfName = nameStr;

                QSettings writeini(CONFIGPATH, QSettings::IniFormat); // 打开ini文件
                if (ispassword) // 选择保存密码
                {
                    writeini.setValue("login/isremember", "true"); // 写ini文件时记录为true
                }
                else // 不保存密码
                {
                    writeini.setValue("login/isremember", "false"); // 写ini文件时记录为false
                }
                writeini.setValue("login/username", uid); // 把账号写入ini文件
                writeini.setValue("login/password", password); // 把密码写入ini文件
                writeini.setValue("login/sflb", sflb); // 把身份写入ini文件

                qDebug() << query.value("admin_name").toString() ;
                mainpage2 *w=new mainpage2();
                w->show();
                close();
            }else
                QMessageBox::warning(this, "登录提示", "密码不正确， 请重新输入！");
        }else
            QMessageBox::warning(this, "登录提示", sfStr+"《"+uid+"》不存在， 请重新输入！");
    }else{
        QMessageBox::warning(this, "登录提示", "请选择登录的身份类型！");
        return;
    }
}


void LoginDialog::on_exitpushButton_clicked()
{
    exit(0);
}


void LoginDialog::on_checkBox_clicked()
{
    // 根据是否记住密码改变标志位
    ispassword = ui->checkBox->isChecked();
}

void LoginDialog::mousePressEvent(QMouseEvent *e)
{
    //鼠标左键
    if(e->button() == Qt::LeftButton)
    {
        m_ptPress = e->pos();
        //qDebug() << pos() << e->pos() << m_ptPress;
        m_bPressed = m_areaMovable.contains(m_ptPress);
    }
}

void LoginDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(m_bPressed)
    {
        qDebug() << pos() << e->pos() << m_ptPress;
        this->move(pos() + e->pos() - m_ptPress);
    }
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *)
{
    m_bPressed = false;
}

//设置鼠标按下的区域
void LoginDialog::setAreaMovable(const QRect rt)
{
    if(m_areaMovable != rt)
    {
        m_areaMovable = rt;
    }
}


void LoginDialog::on_pushButton_2_clicked()
{
    close();
}


void LoginDialog::on_pushButton_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}


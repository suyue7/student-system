#include "mainwindow.h"
#include "logindialog.h"

int MainWindow::sfLB = 0;
QString MainWindow::sfID="";
QString MainWindow::sfName="";
bool MainWindow::dbflag = false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->namelabel->setText("教师：" + MainWindow::sfName);
    ui->uidlabel->setText("ID：" + MainWindow::sfID);

    QRect desktop = QGuiApplication::primaryScreen()->geometry();
    move((desktop.width() - this->width())/2, (desktop.height() - this->height() - 80)/2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectdb(QSqlDatabase& db){
    //连接数据库(加载数据库驱动，返回数据库对象)
    db = QSqlDatabase::addDatabase("QODBC");   //加载MySQL数据库驱动，返回数据库对象
    db.setDatabaseName("persondb");
    db.setHostName("localhost");
    db.setPort(3306);
}


void MainWindow::on_scoreinputpushButton_clicked()
{
    if(sfLB == 1){
        ScoreInputDialog_teacher* seleID = new ScoreInputDialog_teacher();
        seleID->show();
    }else
        QMessageBox::warning(this, "警告", "只有《教师》才能录入学生课程成绩 !");
}


void MainWindow::on_pushButton_clicked()
{
    if(sfLB == 1){
        QueryScoreGraphicsDialog * t = new QueryScoreGraphicsDialog();
        t->show();
    }else
        QMessageBox::warning(this, "警告", "只有《教师》才能查看课程质量分析图表 !");
}


void MainWindow::on_infopushButton_clicked()
{
    if(sfLB == 1){
        TPersonalInfo * t = new TPersonalInfo();
        t->show();
    }else
        QMessageBox::warning(this, "警告", "只有《教师》才能查看课程质量分析图表 !");
}


void MainWindow::on_assessbrowsepushButton_clicked()
{
    if(sfLB == 1){
        AccessBrowseDialog * t = new AccessBrowseDialog();
        t->show();
    }
}


void MainWindow::on_announcementpushButton_clicked()
{
    announcepage_teacher * a = new announcepage_teacher();
    a->show();
}


void MainWindow::on_exitButton_clicked()
{
    LoginDialog * ld = new LoginDialog();
    ld->show();
    this->close();
}


void MainWindow::on_applyButton_clicked()
{
    ApplyDialog *ad = new ApplyDialog();
    ad->show();
}


void MainWindow::on_changepwBtn_clicked()
{
    changepasswd *cp = new changepasswd();
    cp->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    helpwidget *hw = new helpwidget();
    hw->show();
}


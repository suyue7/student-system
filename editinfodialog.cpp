#include "editinfodialog.h"
#include "ui_editinfodialog.h"
#include "mainwindow.h"
#include "tpersonalinfo.h"
#include "ui_tpersonalinfo.h"

EditInfoDialog::EditInfoDialog(QWidget * info, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditInfoDialog),
    changeflag(false)
{
    ui->setupUi(this);

    infowidget = (TPersonalInfo*)info;

    ui->namelineEdit->setText(MainWindow::sfName);
    ui->idlineEdit->setText(MainWindow::sfID);
    ui->namelineEdit->setEnabled(false);
    ui->idlineEdit->setEnabled(false);
    QString sql = QString("SELECT tsex, tphonenumber, temail, tdepartment, taddress FROM teacher_table WHERE tid='%1';").arg(MainWindow::sfID);
    QSqlQuery query;
    query.exec(sql);
    if(query.next()){
        ui->sexlineEdit->setText(query.value("tsex").toString());
        ui->departlineEdit->setText(query.value("tdepartment").toString());
        ui->phonelineEdit->setText(query.value("tphonenumber").toString());
        ui->emaillineEdit->setText(query.value("temail").toString());
        ui->addresslineEdit->setText(query.value("taddress").toString());
    }

    QStringList listData;
    sql=QString("select department from dep_table");
    query.exec(sql);
    while(query.next())
    {
        listData<<query.value(0).toString();
    }
    QCompleter *m_pCompleter = new QCompleter(listData);
    m_pCompleter->setFilterMode(Qt::MatchContains);
    ui->departlineEdit->setCompleter(m_pCompleter);
}

EditInfoDialog::~EditInfoDialog()
{
    delete ui;
}

void EditInfoDialog::on_cancelButton_clicked()
{
    close();
}


void EditInfoDialog::on_saveButton_clicked()
{
    QString sex = ui->sexlineEdit->text();
    QString dep = ui->departlineEdit->text();
    if(sex.isEmpty()){
        QMessageBox::warning(this,"Error","性别不能为空！！请重输");
        return;
    }
    if(sex!="男"&&sex!="女"){
        QMessageBox::warning(this,"Error","性别只能为\"男\"或\"女\"！！请重输");
        return;
    }
    if(dep.isEmpty()){
        QMessageBox::warning(NULL,"Error","院系不能为空！！请重输");
        return;
    }
    QSqlQuery test;
    test.exec(QString("select * from dep_table where dep_table.department='%1'").arg(dep));
    if(!test.next()){
        QMessageBox::warning(NULL,"Error","不存在该学院请重输");
        return;
    }
    changeflag = true;

    QString phone = ui->phonelineEdit->text();
    std::regex r("^1(3|5|8)\\d{9}$");
    std::string userIdString =phone.toStdString();
    bool bValid=std::regex_match(userIdString,r);
    if(!bValid){
        QMessageBox::warning(NULL,"Error","输入的手机不合法！！请重输");
        return;
    }

    QString email = ui->emaillineEdit->text();
    std::regex r2("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
    std::string em =email.toStdString();
    bValid=std::regex_match(em,r2);
    if(!bValid){
        QMessageBox::warning(NULL,"Error","输入的邮箱不合法！！请重输");
        return;
    }

    QString address = ui->addresslineEdit->text();
    std::regex reg("^[\u4e00-\u9fa5]+省[\u4e00-\u9fa5]+市");
    std::string add = address.toStdString();
    bValid = std::regex_match(add, reg);
    if(!bValid){
        QMessageBox::warning(NULL,"Error","输入的家庭住址不合法！！请重输");
        return;
    }

    QSqlQuery query;
    QString updateSql = QString("UPDATE teacher_table SET tsex='%1',tphonenumber='%2',temail='%3',taddress='%4', tdepartment='%5' WHERE tid='%6'").arg(sex,phone,email,address,dep,MainWindow::sfID);
    query.exec(updateSql);
    infowidget->ui->tableWidget->setItem(0, 2, new QTableWidgetItem(sex));
    infowidget->ui->tableWidget->setItem(0, 4, new QTableWidgetItem(dep));
    infowidget->ui->tableWidget->setItem(0, 5, new QTableWidgetItem(phone));
    infowidget->ui->tableWidget->setItem(0, 6, new QTableWidgetItem(email));
    infowidget->ui->tableWidget->setItem(0, 7, new QTableWidgetItem(address));
    close();
}

bool EditInfoDialog::getChangeflag(){
    return changeflag;
}

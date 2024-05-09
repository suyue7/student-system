#include "applydialog.h"
#include "ui_applydialog.h"

ApplyDialog::ApplyDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ApplyDialog)
{
    ui->setupUi(this);

    QStringList data1 = {"A", "B", "C", "D", "E", "F"};
    QStringList data2 = {"1", "2", "3", "4", "5"};
    QStringList data3 = {"01","02","03","04","05","06","07","08","09","10","11","12"};
    // QStringList data4 = {"星期一","星期二","星期三","星期四","星期五","星期六","星期日"};
    // QStringList data5 = {"第一节课","第二节课","第三节课","第四节课","第五节课","第六节课","第七节课","第八节课","第九节课","第十节课","第十一节课"};
    QStringList data6 = {"公必","公选","专必","专选"};
    QStringList data7 = {"论文考查","开卷考试","闭卷考试"};
    ui->comboBox1->addItems(data1);
    ui->comboBox2->addItems(data2);
    ui->comboBox3->addItems(data3);
    ui->classifycomboBox->addItems(data6);
    ui->kcfscomboBox->addItems(data7);

    QStringList listData;
    QString sql=QString("select department from dep_table");
    QSqlQuery query;
    query.exec(sql);
    while(query.next())
    {
        listData<<query.value(0).toString();
    }
    QCompleter *m_pCompleter = new QCompleter(listData);
    m_pCompleter->setFilterMode(Qt::MatchContains);
    ui->deplineEdit->setCompleter(m_pCompleter);
}


ApplyDialog::~ApplyDialog()
{
    delete ui;
}

void ApplyDialog::on_pushButton_clicked()
{
    QString name = ui->namelineEdit->text();
    QString cid = ui->idlineEdit->text();
    QString classify = ui->classifycomboBox->currentText();
    QString cscore = ui->scorelineEdit->text();
    QString dep = ui->deplineEdit->text();
    QString capacity = ui->capacitylineEdit->text();
    QString ctime = ui->timelineEdit->text();
    QString location = ui->comboBox1->currentText()+ui->comboBox2->currentText()+ui->comboBox3->currentText();
    QString kcfs = ui->kcfscomboBox->currentText();
    QSqlQuery test;

    //代码的异常判断块
    if(name=="")
    {
        QMessageBox::warning(NULL,"Error","输入的课程名称不能为空！请重输");
        return;
    }
    else if(dep=="")
    {
        QMessageBox::warning(NULL,"Error","输入课程的开设学院不能为空！请重输");
        return;
    }
    else if(location=="")
    {
        QMessageBox::warning(NULL,"Error","输入的课程地点不能为空！请重输");
        return;
    }

    std::regex r1("^[0-9]{1,3}$");
    std::string ctime_ = ctime.toStdString();
    std::string cscore_ = cscore.toStdString();
    std::string capacity_ = capacity.toStdString();
    bool bValid=std::regex_match(ctime_ ,r1);
    if(!bValid||ctime.toInt()<20||ctime.toInt()>150){
        QMessageBox::warning(this, "警告", "课程课时只能输入20-150中的数字！请重输");
        return;
    }
    bValid=std::regex_match(cscore_ ,r1);
    if(!bValid||cscore.toInt()<=0||cscore.toInt()>8){
        QMessageBox::warning(this, "警告", "课程学分只能输入1-8中的数字！请重输");
        return;
    }
    bValid=std::regex_match(capacity_ ,r1);
    if(!bValid||capacity.toInt()<20||capacity.toInt()>200){
        QMessageBox::warning(this, "警告", "开设人数只能输入20-200中的数字！请重输");
        return;
    }

    // if(ctime.toInt()<20)
    // {
    //     QMessageBox::warning(NULL,"Error","输入的课程课时不能小于20！！请重输");
    //     return;
    // }
    // else if(ctime.toInt()>150)
    // {
    //     QMessageBox::warning(NULL,"Error","输入的课程课时不能大于150了！！请重输");
    //     return;
    // }
    // else if(cscore.toInt()<=0)
    // {
    //     QMessageBox::warning(NULL,"Error","输入的学分不能小于等于0！！请重输");
    //     return;
    // }
    // else if(cscore.toInt()>10)
    // {
    //     QMessageBox::warning(NULL,"Error","输入的学分大于10，异常大！！请重输");
    //     return;
    // }
    // else if(capacity.toInt()<20)
    // {
    //     QMessageBox::warning(NULL,"Error","输入的开设人数不能小于20！！请重输");
    //     return;
    // }
    // else if(capacity.toInt()>200)
    // {
    //     QMessageBox::warning(NULL,"Error","输入的开设人数不能大于200！！请重输");
    //     return;
    // }
    if(!test.exec(QString("select * from class_table where cid='%1'").arg(cid)))
    {
        QMessageBox::warning(NULL,"Error","该课程id已存在！！请重输");
        return;
    }
    test.exec(QString("select * from dep_table where dep_table.department='%1'").arg(dep));
    if(!test.next()){
        QMessageBox::warning(NULL,"Error","不存在该学院请重输");
        return;
    }

    std::regex r2("^[0-9]{4}$");
    std::string cid_ = cid.toStdString();
    bValid=std::regex_match(cid_ ,r2);
    if(!bValid){
        QMessageBox::warning(this, "警告", "课程id需由4位数字组成！请重输");
        return;
    }

    QSqlQuery query;

    QString sql;
    // = QString("select cid from arr_table where tid='%1' AND clocation='%2';").arg(MainWindow::sfID, location);
    // query.exec(sql);
    // if(query.next()){
    //     QMessageBox::warning(this, "警告", "所选上课地点已被占用，请更改上课地点！");
    //     return;
    // }
    sql = QString("INSERT INTO class_table VALUES('%1','%2','%3','%4','%5','%6','%7','%8','%9',%10,%11,'%12',%13);").arg(cid,name,classify,cscore,dep,MainWindow::sfID,location,ctime,capacity,"0","0",kcfs,"0");

    if(query.exec(sql))
        qDebug() << "申请成功！";
    close();
}


void ApplyDialog::on_pushButton_2_clicked()
{
    close();
}


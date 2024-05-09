#include "teacherpage.h"
#include "ui_teacherpage.h"
#include "logindialog.h"
#include <QLatin1Char>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QVector>
#include <QHash>

teacherpage::teacherpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teacherpage)
{
    ui->setupUi(this);
    this->setWindowTitle("教师管理");

    ui->topLabel->lower();
    ui->toclassBtn->setIcon(QIcon("image/class2.png"));
    ui->toclassBtn->setLayoutDirection(Qt::LeftToRight);
    ui->tostudentBtn->setIcon(QIcon("image/student.png"));
    ui->tostudentBtn->setLayoutDirection(Qt::LeftToRight);
    ui->toannouncBtn->setIcon(QIcon("image/announce.png"));
    ui->toannouncBtn->setLayoutDirection(Qt::LeftToRight);
    ui->refreshBtn->setIcon(QIcon("image/right.png"));
    ui->refreshBtn->setLayoutDirection(Qt::RightToLeft);
    ui->pushButton_3->setIcon(QIcon("image/add_1.png"));
    ui->pushButton_3->setLayoutDirection(Qt::LeftToRight);
    ui->pushButton_5->setIcon(QIcon("image/cancel.png"));
    ui->pushButton_5->setLayoutDirection(Qt::LeftToRight);
    ui->pushButton_4->setIcon(QIcon("image/assess.png"));
    ui->pushButton_4->setLayoutDirection(Qt::LeftToRight);
    ui->pushButton->setIcon(QIcon("image/right.png"));
    ui->pushButton->setLayoutDirection(Qt::RightToLeft);
    ui->deleteBtn->setIcon(QIcon("image/cancel.png"));
    ui->deleteBtn->setLayoutDirection(Qt::RightToLeft);

    QPixmap qp1("image/person.png");
    ui->picLabel->setPixmap(qp1);
    ui->picLabel->setScaledContents(true);
    ui->picLabel->show();

    this->myDataBase.DBOpen();
    this->dataTableModel=new QStandardItemModel();
    this->selection=new QItemSelectionModel(dataTableModel);
    this->setTabletInfo();
    this->getDatabaseInfo();
    //将设计好的表格样式装载到表格上
    ui->teacherTable->setModel(this->dataTableModel);
    QObject::connect(this->dataTableModel,SIGNAL(dataChanged(const QModelIndex&,const QModelIndex &)),ui->teacherTable,SLOT(update()));
    ui->control_page->setCurrentIndex(0);

    QString sql=QString("select * from teacher_table");
    QSqlQuery query;
    query.exec(sql);
    while(query.next())
    {
        listData<<query.value("tid").toString();
        listData<<query.value("tname").toString();
    }
    QString sql2=QString("select * from dep_table");
    QSqlQuery query2;
    query2.exec(sql2);
    while(query.next())
    {
        listData<<query.value("department").toString();
    }
    listData<<"教授"<<"副教授"<<"讲师";
    QCompleter *m_pCompleter = new QCompleter(listData);
    m_pCompleter->setFilterMode(Qt::MatchContains);
    ui->lineEdit->setCompleter(m_pCompleter);

    //评教分数展示，同一课程取平均分
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"课程id"<<"课程名称"<<"任课老师"<<"评分");
    ui->tableWidget->setColumnWidth(0,60);
    ui->tableWidget->setColumnWidth(1,120);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,80);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    int i=0,sum=0,s=0;
    query.clear();
    sql=QString("SELECT * FROM class_table");
    query.exec(sql);
    while (query.next())
    {
        if (query.value("is_open").toInt()==0||query.value("is_apply").toInt()==0) break;  //没开课或没开放评教
        QString thisId=query.value("cid").toString();  //当前课程id
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(thisId));  //id
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value("cname").toString()));  //名称

        query2.clear();
        sql=QString("SELECT * FROM teacher_table WHERE tid='%1'").arg(query.value("tid").toString());
        query2.exec(sql);   //通过id找老师姓名
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query2.value("tname").toString()));  //老师

        query2.clear();
        sql=QString("SELECT * FROM selectedlesson WHERE cid='%1'").arg(thisId);
        query2.exec(sql);
        sum=0;
        s=0;
        while (query2.next())
        {
            if (query2.value("cid").toString()!=thisId)
                continue;
            sum+=query2.value("tscore").toInt();
            s++;
        }

        double ave=sum*1.0/s;
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(ave,'f',2)));  //平均分数

        i++;
    }
}

teacherpage::~teacherpage()
{
    delete ui;
}
//查看教师信息表格
void teacherpage::setTabletInfo()
{
    //设置表头样式
    this->dataTableModel->setHorizontalHeaderItem(0,new QStandardItem("学工号"));
    this->dataTableModel->setHorizontalHeaderItem(1,new QStandardItem("密码"));
    this->dataTableModel->setHorizontalHeaderItem(2,new QStandardItem("姓名"));
    this->dataTableModel->setHorizontalHeaderItem(3,new QStandardItem("性别"));
    this->dataTableModel->setHorizontalHeaderItem(4,new QStandardItem("所属院系"));
    this->dataTableModel->setHorizontalHeaderItem(5,new QStandardItem("职称"));
    this->dataTableModel->setHorizontalHeaderItem(6,new QStandardItem("电话号码"));
    this->dataTableModel->setHorizontalHeaderItem(7,new QStandardItem("邮箱"));
    //设置列宽
    ui->teacherTable->setColumnWidth(0,100);
    ui->teacherTable->setColumnWidth(1,100);
    ui->teacherTable->setColumnWidth(2,70);
    ui->teacherTable->setColumnWidth(3,150);
    ui->teacherTable->setColumnWidth(4,80);
    ui->teacherTable->setColumnWidth(5,200);
    ui->teacherTable->setColumnWidth(6,200);


}
void teacherpage::getDatabaseInfo()
{
    QSqlQuery sql;
    sql.prepare("select * from teacher_table");
    sql.exec();
    int row=0;
    while(sql.next())
    {
        this->dataTableModel->setItem(row,0,new QStandardItem(sql.value("tid").toString()));
        this->dataTableModel->setItem(row,1,new QStandardItem(sql.value("tpasswd").toString()));
        this->dataTableModel->setItem(row,2,new QStandardItem(sql.value("tname").toString()));
        this->dataTableModel->setItem(row,3,new QStandardItem(sql.value("tsex").toString()));
        this->dataTableModel->setItem(row,4,new QStandardItem(sql.value("tdepartment").toString()));
        this->dataTableModel->setItem(row,5,new QStandardItem(sql.value("tjobtitle").toString()));
        this->dataTableModel->setItem(row,6,new QStandardItem(sql.value("tphonenumber").toString()));
        this->dataTableModel->setItem(row,7,new QStandardItem(sql.value("temail").toString()));
        row++;
    }
    sql.clear();
}

void teacherpage::on_pushButton_3_clicked()
{
    ui->control_page->setCurrentIndex(0);
}


void teacherpage::on_pushButton_5_clicked()
{
    ui->control_page->setCurrentIndex(1);
}


void teacherpage::on_pushButton_4_clicked()
{
    ui->control_page->setCurrentIndex(2);
}

void teacherpage::on_deleteBtn_clicked()
{


    //else
    //{
        QString deletename=ui->deleteEdit->text();
        if (deletename==""){QMessageBox::warning(NULL,"Error","请输入需删除的信息！");return;}
            QSqlQuery query;
            QString sql=QString("SELECT * from teacher_table where tid='%1'").arg(deletename);
            query.exec(sql);
            if(query.next())
            {
                QMessageBox::StandardButton box;
                box = QMessageBox::question(this, "提示", "确定要删除吗?", QMessageBox::Yes|QMessageBox::No);
                if(box==QMessageBox::No)return;

                sql=QString("delete from teacher_table where tid='%1'").arg(deletename);
                query.exec(sql);

                QMessageBox::information(NULL,"温馨提示","删除成功！");
                qDebug()<<"删除成功";
                this->dataTableModel->clear();
                setTabletInfo();
                getDatabaseInfo();
            }
            else
            {
                QMessageBox::warning(NULL,"Error","输入信息有误！");
                qDebug()<<"删除失败";
            }
           query.clear();
    //}

}

void teacherpage::on_refreshBtn_clicked()
{
    QString id=ui->idEdit->text();
    QString passwd=ui->passwdEdit->text();
    QString name=ui->nameEdit->text();
    QString sex;

    int sexnum=ui->sexBox->currentIndex();
    if(sexnum==0)sex="男";
    else if(sexnum==1)sex="女";
    QString department=ui->departmentEdit->text();

    QString job;
    int jobnum=ui->jobBox->currentIndex();
    if(jobnum==0)job="教授";
    else if(jobnum==1)job="副教授";
    else if(jobnum==2)job="讲师";
    QString number=ui->numberEdit->text();
    QString email=ui->emailEdit->text();

    //这里要好好想想异常判断，暂时先给这些
    if(id=="")
    {
           QMessageBox::warning(NULL,"Error","输入的学工号不能为空！请重输");
           return;
    }
    QSqlQuery aaquery;
    aaquery.clear();
    QString aasql=QString("SELECT * FROM teacher_table WHERE tid='%1'").arg(id);
    aaquery.exec(aasql);
    if (aaquery.next()) {QMessageBox::warning(NULL,"Error","该学工号已被占用！请重输");return;}
    if (id.length()!=5) {QMessageBox::warning(NULL,"Error","学工号须为5位字母或数字！请重输");return;}
    for (int i=0;i<5;i++)
    {
        if (id[i]>='0'&&id[i]<='9') continue;
        if (id[i]>='a'&&id[i]<='z') continue;
        if (id[i]>='A'&&id[i]<='Z') continue;
        QMessageBox::warning(NULL,"Error","学工号须为5位字母或数字！请重输");
        return;
    }
    if(passwd.length()<6||passwd.length()>15){
        QMessageBox::warning(this, "警告", "密码长度须为6-15位！请重输");
        return;
    }
    for (int i=0;i<passwd.length();i++)
    {
        if (passwd[i]>='0'&&passwd[i]<='9') continue;
        if (passwd[i]>='a'&&passwd[i]<='z') continue;
        if (passwd[i]>='A'&&passwd[i]<='Z') continue;
        QMessageBox::warning(this,"警告","密码只能含有数字和字母！");
        return;
    }
    if(name=="")
    {
           QMessageBox::warning(NULL,"Error","输入姓名不能为空！请重输");
           return;
    }
    for (int i=0;i<name.length();i++)
        if (name[i]>='0'&&name[i]<='9')
            {QMessageBox::warning(NULL,"Error","姓名不能含有数字！请重输");return;}
    if (name.length()<2||name.length()>8)
    {
        QMessageBox::warning(NULL,"Error","姓名必须为2-8位！请重输");
        return;
    }

    QRegularExpression rx("^[\u4e00-\u9fa5]+$");   //使用正则表达式判断是否为纯汉字
    QRegularExpressionMatch mat=rx.match(name);   //创建匹配器
    if (!mat.hasMatch())    //判断是否匹配成功
    {
        QMessageBox::warning(NULL,"Error","姓名必须为纯中文！请重输");
        return;
    }

    QSqlQuery test;
    test.exec(QString("select * from dep_table where dep_table.department='%1'").arg(department));
    if(!test.next()){
        QMessageBox::warning(NULL,"Error","不存在该学院！请重输");
        return;
    }

    std::regex r("^1(3|5|8)\\d{9}$");
    std::string userIdString =number.toStdString();
    bool bValid=std::regex_match(userIdString,r);
    if(!bValid){
        QMessageBox::warning(NULL,"Error","输入的手机不合法！请重输");
        return;
    }

    if (email!="")
    {
        std::regex r2("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
        std::string em=email.toStdString();
        bool bValidm=std::regex_match(em,r2);
        if(!bValidm){
            QMessageBox::warning(NULL,"Error","输入的邮箱不合法！请重输");
            return;
        }
    }

    QSqlQuery query;
    QString sql=QString("insert into teacher_table(tid,tpasswd,tname,tsex,tdepartment,tjobtitle,tphonenumber,temail)values('%1','%2','%3','%4','%5','%6','%7','%8')").arg(id).arg(passwd).arg(name).arg(sex).arg(department).arg(job).arg(number).arg(email);
        if(query.exec(sql))
        {
            qDebug()<<"创建教师资料成功";
        }
        else
        {
            qDebug()<<"创建教师资料失败";
        }
        this->dataTableModel->clear();
        this->setTabletInfo();
        this->getDatabaseInfo();
}


void teacherpage::on_toclassBtn_clicked()
{
        mainpage2* w=new mainpage2();
        w->show();
        this->close();
}


void teacherpage::on_tostudentBtn_clicked()
{
        studentpage* w=new studentpage();
        w->show();
        this->close();
}


void teacherpage::on_toannouncBtn_clicked()
{
        announcepage* w=new announcepage();
        w->show();
        this->close();
}


void teacherpage::on_searchBtn_clicked()
{
        int index=ui->comboBox->currentIndex();
        //读取查询的内容
        QString searchname=ui->lineEdit->text();
        qDebug()<<searchname;
        this->dataTableModel->clear();
        QSqlQuery query;
        QString sql;
        //按照教师id
        if(index==0)
        {
            sql=QString("select * from teacher_table where tid='%1'").arg(searchname);
        }
        //按照教师姓名
        else if(index==1)
        {
            sql=QString("select * from teacher_table where tname='%1'").arg(searchname);
        }
        //按照所属院系
        else if(index==2)
        {
            sql=QString("select * from teacher_table where tdepartment='%1'").arg(searchname);
        }
        //按照性别
        else if(index==3)
        {
            sql=QString("select * from teacher_table where tsex='%1'").arg(searchname);
        }
        else if(index==4)
        {
            sql=QString("select * from teacher_table where tjobtitle='%1'").arg(searchname);
        }
        //显示全部
        else
        {
            sql=QString("select * from teacher_table ");
        }
        if(query.exec(sql))
        {
            qDebug()<<"查询成功";
            ui->lineEdit->clear();
            int row=0;
            while(query.next())
            {
            this->dataTableModel->setItem(row,0,new QStandardItem(query.value("tid").toString()));
            this->dataTableModel->setItem(row,1,new QStandardItem(query.value("tpasswd").toString()));
            this->dataTableModel->setItem(row,2,new QStandardItem(query.value("tname").toString()));
            this->dataTableModel->setItem(row,3,new QStandardItem(query.value("tsex").toString()));
            this->dataTableModel->setItem(row,4,new QStandardItem(query.value("tdepartment").toString()));
            this->dataTableModel->setItem(row,5,new QStandardItem(query.value("tjobtitle").toString()));
            this->dataTableModel->setItem(row,5,new QStandardItem(query.value("tphonenumber").toString()));
            this->dataTableModel->setItem(row,6,new QStandardItem(query.value("temail").toString()));
            row++;
            }
        }
        else
        {
            QMessageBox::warning(NULL,"查询失败","数据库没有该信息");
        }
        query.clear();
}


void teacherpage::on_pushButton_clicked()
{
    //实现双击更新文本之后直接修改数据库
        //显示修改界面
    for (int row=0;row<dataTableModel->rowCount();row++)
    {
        //row=ui->teacherTable->currentIndex().row();
        //qDebug()<<row;
        QModelIndex index1=dataTableModel->index(row,0);
        QModelIndex index2=dataTableModel->index(row,1);
        QModelIndex index3=dataTableModel->index(row,2);
        QModelIndex index4=dataTableModel->index(row,3);
        QModelIndex index5=dataTableModel->index(row,4);
        QModelIndex index6=dataTableModel->index(row,5);
        QModelIndex index7=dataTableModel->index(row,6);
        QModelIndex index8=dataTableModel->index(row,7);
        QString id=dataTableModel->data(index1).toString();
        qDebug()<<id;
        QString passwd=dataTableModel->data(index2).toString();
        QString name=dataTableModel->data(index3).toString();
        QString sex=dataTableModel->data(index4).toString();
        QString department=dataTableModel->data(index5).toString();

        QString jobtitle=dataTableModel->data(index6).toString();
        QString phonenumber=dataTableModel->data(index7).toString();
        QString email=dataTableModel->data(index8).toString();

        //这里要好好想想异常判断，暂时先给这些
        if(id=="")
        {
            QMessageBox::warning(NULL,"Error","输入的学工号不能为空！请重输");
            return;
        }
        QHash<QString,int> idHash;
        for (int i=0;i<dataTableModel->rowCount();i++)
        {
            QModelIndex idindex=dataTableModel->index(i,0);
            QString id1=dataTableModel->data(idindex).toString();
            if (idHash.contains(id1))
                {QMessageBox::warning(NULL,"Error","学工号不能重复！请重输");return;}
            idHash[id1]=1;
        }
        if (id.length()!=5) {QMessageBox::warning(NULL,"Error","学工号须为5位字母或数字！请重输");return;}
        for (int i=0;i<5;i++)
        {
            if (id[i]>='0'&&id[i]<='9') continue;
            if (id[i]>='a'&&id[i]<='z') continue;
            if (id[i]>='A'&&id[i]<='Z') continue;
            QMessageBox::warning(NULL,"Error","学工号须为5位字母或数字！请重输");
            return;
        }

        if(name=="")
        {
            QMessageBox::warning(NULL,"Error","输入姓名不能为空！请重输");
            return;
        }
        for (int i=0;i<name.length();i++)
            if (name[i]>='0'&&name[i]<='9')
                {QMessageBox::warning(NULL,"Error","姓名不能含有数字！请重输");return;}
        if (name.length()<2||name.length()>8)
        {
            QMessageBox::warning(NULL,"Error","姓名必须为2-8位！请重输");
            return;
        }

        QRegularExpression rx("^[\u4e00-\u9fa5]+$");   //使用正则表达式判断是否为纯汉字
        QRegularExpressionMatch mat=rx.match(name);   //创建匹配器
        if (!mat.hasMatch())    //判断是否匹配成功
        {
            QMessageBox::warning(NULL,"Error","姓名必须为纯中文！请重输");
            return;
        }

        if(sex!="男"&&sex!="女")
        {
            QMessageBox::warning(NULL,"Error","输入性别不符合规范！！请重输");
            return;
        }
        if(passwd.length()<6||passwd.length()>15)
        {
            QMessageBox::warning(this, "警告", "新密码长度需为6-15位！请重输");
            return;
        }
        for (int i=0;i<passwd.length();i++)
        {
            if (passwd[i]>='0'&&passwd[i]<='9') continue;
            if (passwd[i]>='a'&&passwd[i]<='z') continue;
            if (passwd[i]>='A'&&passwd[i]<='Z') continue;
            QMessageBox::warning(this,"警告","密码只能含有数字和字母！");
            return;
        }
        QSqlQuery test;
        test.exec(QString("select * from dep_table where dep_table.department='%1'").arg(department));
        if(!test.next()){
            QMessageBox::warning(NULL,"Error","不存在该学院，请重输！");
            return;
        }

        if(jobtitle!="教授"&&jobtitle!="副教授"&&jobtitle!="讲师")
        {
            QMessageBox::warning(NULL,"Error","不存在该职称！！请重输");
            return;
        }

        if (phonenumber.length()!=11) {QMessageBox::warning(this,"警告","输入的手机不合法！请重输");return;}
        std::regex r("^1(3|5|8)\\d{9}$");
        std::string userIdString =phonenumber.toStdString();
        bool bValid=std::regex_match(userIdString,r);
        if(!bValid){
            QMessageBox::warning(NULL,"Error","输入的手机不合法！请重输");
            return;
        }

        if (email!="")
        {
            std::regex r2("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
            std::string em=email.toStdString();
            bool bValidm=std::regex_match(em,r2);
            if(!bValidm){
                QMessageBox::warning(NULL,"Error","输入的邮箱不合法！请重输");
                return;
            }
        }

        QSqlQuery query;
        QString sql=QString("update teacher_table set tpasswd='%1',tname='%2',tsex='%3',tdepartment='%4',tjobtitle='%5',tphonenumber='%6',temail='%7' where tid='%8'").arg(passwd).arg(name).arg(sex).arg(department).arg(jobtitle).arg(phonenumber).arg(email).arg(id);
        query.exec(sql);
        query.clear();
    }
    QMessageBox::information(NULL,"温馨提示","修改教师资料成功！");
}


void teacherpage::on_quitBtn_clicked()
{
    this->close();
    LoginDialog *ld=new LoginDialog(NULL);
    ld->show();
}


void teacherpage::on_teacherTable_clicked(const QModelIndex &index)
{
    int row=ui->teacherTable->currentIndex().row();
    QModelIndex idcol=dataTableModel->index(row,0);
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"课程id"<<"课程名称"<<"任课老师"<<"评分");
    ui->tableWidget->setColumnWidth(0,60);
    ui->tableWidget->setColumnWidth(1,120);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,80);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

    QString tid=dataTableModel->data(idcol).toString();
    QSqlQuery query,query1;
    query.clear();
    QString sql=QString("SELECT * FROM class_table WHERE tid='%1' AND is_open=1").arg(tid);  //找到该老师教的所有课
    qDebug()<<"sql1："<<sql;
    query.exec(sql);
    int i=0;
    while (query.next())
    {
        QString lesId=query.value("cid").toString();
        sql=QString("SELECT * FROM selectedlesson WHERE cid='%1'").arg(lesId);  //在选课表里面找到当前课程
        qDebug()<<"sql"<<i+2<<"："<<sql;
        query1.clear();
        query1.exec(sql);
        int tmpScore=0,sum=0;
        while (query1.next())
        {
            tmpScore+=query1.value("tscore").toInt();
            qDebug()<<"tmpScore"<<tmpScore;
            sum++;
        }
        double thisScore=tmpScore*1.0/sum;
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(lesId));  //课程id
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value("cname").toString()));  //课程名称
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(tid));  //任课教师
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(thisScore,'f',2)));  //平均分
        i++;
    }
}


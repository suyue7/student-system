#include "studentpage.h"
#include "ui_studentpage.h"
#include "logindialog.h"
#include <QHash>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

studentpage::studentpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::studentpage)
{
    ui->setupUi(this);

    this->setWindowTitle("学生管理");
    ui->topLabel->lower();
    ui->toclassBtn->setIcon(QIcon("image/class2.png"));
    ui->toclassBtn->setLayoutDirection(Qt::LeftToRight);
    ui->toteacherBtn->setIcon(QIcon("image/teacher.png"));
    ui->toteacherBtn->setLayoutDirection(Qt::LeftToRight);
    ui->toanounceBtn->setIcon(QIcon("image/announce.png"));
    ui->toanounceBtn->setLayoutDirection(Qt::LeftToRight);
    ui->deleterow->setIcon(QIcon("image/wrong.png"));
    ui->deleterow->setLayoutDirection(Qt::LeftToRight);
    ui->pushButton->setIcon(QIcon("image/add_1.png"));
    ui->pushButton->setLayoutDirection(Qt::LeftToRight);
    ui->pushButton_2->setIcon(QIcon("image/edit.png"));
    ui->pushButton_2->setLayoutDirection(Qt::LeftToRight);
    ui->pushButton_3->setIcon(QIcon("image/cancel.png"));
    ui->pushButton_3->setLayoutDirection(Qt::LeftToRight);
    ui->refreshBtn->setIcon(QIcon("image/right.png"));
    ui->refreshBtn->setLayoutDirection(Qt::RightToLeft);
    ui->scoreBtn->setIcon(QIcon("image/right.png"));
    ui->scoreBtn->setLayoutDirection(Qt::RightToLeft);
    ui->confirmBtn->setIcon(QIcon("image/right.png"));
    ui->confirmBtn->setLayoutDirection(Qt::RightToLeft);
    ui->deleteBtn->setIcon(QIcon("image/cancel.png"));
    ui->deleteBtn->setLayoutDirection(Qt::RightToLeft);

    QPixmap qp1("image/person.png");
    ui->picLabel->setPixmap(qp1);
    ui->picLabel->setScaledContents(true);
    ui->picLabel->show();

    this->myDataBase.DBOpen();
    this->dataTableModel=new QStandardItemModel();
    this->scoreTableModel=new QStandardItemModel();
    this->selection=new QItemSelectionModel(dataTableModel);
    //设置表格,现在测试的是课程表格
    this->setTabletInfo();

    //设置表格信息
    this->getDatabaseInfo();
    //将设计好的表格样式装载到表格上
    ui->studentTable->setModel(this->dataTableModel);
    ui->scoretable->setModel(this->scoreTableModel);
    //为tableview设置数据模型和选择模型
    ui->studentTable->setSelectionModel(selection);
    //设置选中模式为整行选中
    ui->studentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    QObject::connect(this->dataTableModel,SIGNAL(dataChanged(const QModelIndex&,const QModelIndex &)),ui->studentTable,SLOT(update()));
    //设置默认表格为新增页面
    ui->searchbox->setCurrentIndex(0);

    QString sql=QString("select * from dep_table");
    QSqlQuery query;
    query.exec(sql);
    while(query.next())
    {
        listData<<query.value("department").toString();
    }
    listData<<"男";
    listData<<"女";
    QString sql2=QString("select * from student_table");
    QSqlQuery query2;
    query2.exec(sql2);
    while(query2.next())
    {
        listData<<query2.value("sid").toString();
        listData<<query2.value("sname").toString();
    }
    QCompleter *m_pCompleter = new QCompleter(listData);
    m_pCompleter->setFilterMode(Qt::MatchContains);
    ui->key_Edit->setCompleter(m_pCompleter);
}

studentpage::~studentpage()
{
    delete ui;
}

//获取表格信息
void studentpage::setTabletInfo()
{
    //设置表头样式
    this->dataTableModel->setHorizontalHeaderItem(0,new QStandardItem("学生id"));
    this->dataTableModel->setHorizontalHeaderItem(1,new QStandardItem("密码"));
    this->dataTableModel->setHorizontalHeaderItem(2,new QStandardItem("姓名"));
    this->dataTableModel->setHorizontalHeaderItem(3,new QStandardItem("性别"));
    this->dataTableModel->setHorizontalHeaderItem(4,new QStandardItem("所属院系"));
    this->dataTableModel->setHorizontalHeaderItem(5,new QStandardItem("电话号码"));
    this->dataTableModel->setHorizontalHeaderItem(6,new QStandardItem("住址"));

    this->scoreTableModel->setHorizontalHeaderItem(0,new QStandardItem("学生id"));
    this->scoreTableModel->setHorizontalHeaderItem(1,new QStandardItem("课程id"));
    this->scoreTableModel->setHorizontalHeaderItem(2,new QStandardItem("分数"));

    //设置列宽
    ui->studentTable->setColumnWidth(0,100);
    ui->studentTable->setColumnWidth(1,200);
    ui->studentTable->setColumnWidth(2,100);
    ui->studentTable->setColumnWidth(3,70);
    ui->studentTable->setColumnWidth(4,150);
    ui->studentTable->setColumnWidth(5,200);
    ui->studentTable->setColumnWidth(6,200);


    ui->scoretable->setColumnWidth(0,100);
    ui->scoretable->setColumnWidth(1,100);
    ui->scoretable->setColumnWidth(2,100);
}
void studentpage::getDatabaseInfo()
{
    QSqlQuery query;
    query.prepare("select * from student_table");
    query.exec();
    int row=0;
    while(query.next())
    {
        this->dataTableModel->setItem(row,0,new QStandardItem(query.value("sid").toString()));
        this->dataTableModel->setItem(row,1,new QStandardItem(query.value("spasswd").toString()));
        this->dataTableModel->setItem(row,2,new QStandardItem(query.value("sname").toString()));
        this->dataTableModel->setItem(row,3,new QStandardItem(query.value("ssex").toString()));
        this->dataTableModel->setItem(row,4,new QStandardItem(query.value("sdepartment").toString()));
        this->dataTableModel->setItem(row,5,new QStandardItem(query.value("sphonenumber").toString()));
        this->dataTableModel->setItem(row,6,new QStandardItem(query.value("saddress").toString()));
        row++;
    }
    query.clear();
}

void studentpage::on_toclassBtn_clicked()
{
    mainpage2* w=new mainpage2();
    w->show();
    this->close();
}


void studentpage::on_toteacherBtn_clicked()
{
    teacherpage* w=new teacherpage();
    w->show();
    this->close();
}


void studentpage::on_toanounceBtn_clicked()
{
    announcepage* w=new announcepage();
    w->show();
    this->close();
}


void studentpage::shownew()
{
    this->dataTableModel->clear();
    this->setTabletInfo();
    //将设计好的表格样式装载到表格上
    ui->studentTable->setModel(this->dataTableModel);
    QSqlQuery query;
    QString sql=QString("select * from student_table");
    if(query.exec(sql))
    {
        qDebug()<<"查询成功";
        int row=0;
        while(query.next())
        {
            this->dataTableModel->setItem(row,0,new QStandardItem(query.value("sid").toString()));
            this->dataTableModel->setItem(row,1,new QStandardItem(query.value("spasswd").toString()));
            this->dataTableModel->setItem(row,2,new QStandardItem(query.value("sname").toString()));
            this->dataTableModel->setItem(row,3,new QStandardItem(query.value("ssex").toString()));
            this->dataTableModel->setItem(row,4,new QStandardItem(query.value("sdepartment").toString()));
            this->dataTableModel->setItem(row,5,new QStandardItem(query.value("sphonenumber").toString()));
            this->dataTableModel->setItem(row,6,new QStandardItem(query.value("saddress").toString()));
            row++;
        }
    }
    else
    {
        qDebug()<<"查询失败";
        QMessageBox::warning(NULL,"Error","查询失败！");
    }
    query.clear();
    ui->studentTable->setColumnWidth(1,100);
}
void studentpage::on_searchBtn_clicked()
{
    int index=ui->comboBox->currentIndex();
    //读取查询的内容
    QString searchname=ui->key_Edit->text();
    qDebug()<<searchname;
    this->dataTableModel->clear();
    this->setTabletInfo();
    //将设计好的表格样式装载到表格上
    ui->studentTable->setModel(this->dataTableModel);
    //按照学生姓名
    if(index==0)
    {
        QSqlQuery query;
        QString sql=QString("select * from student_table where sname='%1'").arg(searchname);
        if(query.exec(sql))
        {
            qDebug()<<"查询成功";
            int row=0;
            while(query.next())
            {
                this->dataTableModel->setItem(row,0,new QStandardItem(query.value("sid").toString()));
                this->dataTableModel->setItem(row,1,new QStandardItem(query.value("spasswd").toString()));
                this->dataTableModel->setItem(row,2,new QStandardItem(query.value("sname").toString()));
                this->dataTableModel->setItem(row,3,new QStandardItem(query.value("ssex").toString()));
                this->dataTableModel->setItem(row,4,new QStandardItem(query.value("sdepartment").toString()));
                this->dataTableModel->setItem(row,5,new QStandardItem(query.value("sphonenumber").toString()));
                this->dataTableModel->setItem(row,6,new QStandardItem(query.value("saddress").toString()));
                row++;
            }
        }
        else
        {
           QMessageBox::warning(NULL,"查询失败","数据库没有该信息");
        }
        query.clear();
    }
    //按照学号
    else if(index==1)
    {
        QSqlQuery query;
        QString sql=QString("select * from student_table where sid='%1'").arg(searchname);
        if(query.exec(sql))
        {
            qDebug()<<"查询成功";
            int row=0;
            while(query.next())
            {
                this->dataTableModel->setItem(row,0,new QStandardItem(query.value("sid").toString()));
                this->dataTableModel->setItem(row,1,new QStandardItem(query.value("spasswd").toString()));
                this->dataTableModel->setItem(row,2,new QStandardItem(query.value("sname").toString()));
                this->dataTableModel->setItem(row,3,new QStandardItem(query.value("ssex").toString()));
                this->dataTableModel->setItem(row,4,new QStandardItem(query.value("sdepartment").toString()));
                this->dataTableModel->setItem(row,5,new QStandardItem(query.value("sphonenumber").toString()));
                this->dataTableModel->setItem(row,6,new QStandardItem(query.value("saddress").toString()));
                row++;
            }
        }
        else
        {
            QMessageBox::warning(NULL,"查询失败","数据库没有该信息");
        }
        query.clear();
    }
    //按照所属院系
    else if(index==2)
    {
        QSqlQuery query;
        QString sql=QString("select * from student_table where sdepartment='%1'").arg(searchname);
        if(query.exec(sql))
        {
            qDebug()<<"查询成功";
            int row=0;
            while(query.next())
            {
                this->dataTableModel->setItem(row,0,new QStandardItem(query.value("sid").toString()));
                this->dataTableModel->setItem(row,1,new QStandardItem(query.value("spasswd").toString()));
                this->dataTableModel->setItem(row,2,new QStandardItem(query.value("sname").toString()));
                this->dataTableModel->setItem(row,3,new QStandardItem(query.value("ssex").toString()));
                this->dataTableModel->setItem(row,4,new QStandardItem(query.value("sdepartment").toString()));
                this->dataTableModel->setItem(row,5,new QStandardItem(query.value("sphonenumber").toString()));
                this->dataTableModel->setItem(row,6,new QStandardItem(query.value("saddress").toString()));
                row++;
            }
        }
        else
        {
            QMessageBox::warning(NULL,"查询失败","数据库没有该信息");
        }
        query.clear();
    }
    //按照性别
    else if(index==3)
    {
        QSqlQuery query;
        QString sql=QString("select * from student_table where ssex='%1'").arg(searchname);
        if(query.exec(sql))
        {
            qDebug()<<"查询成功";
            int row=0;
            while(query.next())
            {
                this->dataTableModel->setItem(row,0,new QStandardItem(query.value("sid").toString()));
                this->dataTableModel->setItem(row,1,new QStandardItem(query.value("spasswd").toString()));
                this->dataTableModel->setItem(row,2,new QStandardItem(query.value("sname").toString()));
                this->dataTableModel->setItem(row,3,new QStandardItem(query.value("ssex").toString()));
                this->dataTableModel->setItem(row,4,new QStandardItem(query.value("sdepartment").toString()));
                this->dataTableModel->setItem(row,5,new QStandardItem(query.value("sphonenumber").toString()));
                this->dataTableModel->setItem(row,6,new QStandardItem(query.value("saddress").toString()));
                row++;
            }
        }
        else
        {
            QMessageBox::warning(NULL,"查询失败","数据库没有该信息");
        }
        query.clear();
    }
    //显示全部
    else
    {
        ui->key_Edit->clear();
        shownew();
    }
}

void studentpage::on_studentTable_clicked(const QModelIndex &index)
{
    //显示修改界面
    int row=ui->studentTable->currentIndex().row();
    qDebug()<<row;
    QModelIndex index1=dataTableModel->index(row,0);
    QModelIndex index2=dataTableModel->index(row,1);
    QModelIndex index3=dataTableModel->index(row,2);
    QModelIndex index4=dataTableModel->index(row,3);
    QModelIndex index5=dataTableModel->index(row,4);
    QModelIndex index6=dataTableModel->index(row,5);
    QModelIndex index7=dataTableModel->index(row,6);
    QString id=dataTableModel->data(index1).toString();
    qDebug()<<id;
    QString passwd=dataTableModel->data(index2).toString();
    QString name=dataTableModel->data(index3).toString();
    QString sex=dataTableModel->data(index4).toString();
    if(sex=="男")ui->sexBox->setCurrentIndex(0);
    else if(sex=="女")ui->sexBox->setCurrentIndex(1);
    QString department=dataTableModel->data(index5).toString();
    QString phone=dataTableModel->data(index6).toString();
    QString address=dataTableModel->data(index7).toString();
    ui->searchbox->setCurrentIndex(1);
    ui->idEdit->setText(id);
    ui->passEdit->setText(passwd);
    ui->nameEdit->setText(name);
    ui->depEdit->setText(department);
    ui->phoneEdit->setText(phone);
    ui->addEdit->setText(address);
    //显示该学生成绩，小框双击可以修改，然后录入成绩可以保存更改
    this->scoreTableModel->clear();
    this->scoreTableModel->setHorizontalHeaderItem(0,new QStandardItem("学生id"));
    this->scoreTableModel->setHorizontalHeaderItem(1,new QStandardItem("课程id"));
    this->scoreTableModel->setHorizontalHeaderItem(2,new QStandardItem("分数"));
    QSqlQuery query;
    QString sql=QString("select * from score_table where sid='%1'").arg(id);
    if(query.exec(sql))
    {
        qDebug()<<"成绩查询成功";
        int row=0;

        while(query.next())
        {
            QStandardItem *item1=new QStandardItem(query.value("sid").toString());
            QStandardItem *item2=new QStandardItem(query.value("cid").toString());
            QStandardItem *item3=new QStandardItem(query.value("sscore").toString());
            this->scoreTableModel->setItem(row,0,item1);
            this->scoreTableModel->setItem(row,1,item2);
            this->scoreTableModel->setItem(row,2,item3);
            item1->setFlags(item1->flags()&~Qt::ItemIsEditable);
            item2->setFlags(item1->flags()&~Qt::ItemIsEditable);
            row++;
        }
    }
    else
    {
        qDebug()<<"成绩查询失败";
        QMessageBox::warning(NULL,"查询失败","数据库没有该学生成绩信息！");
//        box = QMessageBox::question(this, "提示", "需要登记该学生成绩吗?", QMessageBox::Yes|QMessageBox::No);
//        if(box==QMessageBox::No)return;
//        else
//        {
//        }
    }
}

void studentpage::on_deleterow_clicked()
{
    int row=ui->studentTable->currentIndex().row();
    if (row==-1) {QMessageBox::warning(NULL,"Error","请选择需要删除信息的学生！");return;}
    QMessageBox::StandardButton box;
    box = QMessageBox::question(this, "提示", "确定要删除这一行的内容吗?", QMessageBox::Yes|QMessageBox::No);
    if(box==QMessageBox::No)return;
    else
    {
        row=ui->studentTable->currentIndex().row();
        QModelIndex index1=dataTableModel->index(row,0);
        qDebug()<<row;
        QString deletename=dataTableModel->data(index1).toString();

        //按照课程id
        QSqlQuery query;
        QString sql=QString("delete from student_table where sid='%1'").arg(deletename);
        query.exec(sql);
        QMessageBox::information(NULL,"温馨提示","删除成功！");
        qDebug()<<"删除成功";
        query.clear();
        shownew();
    }
}


void studentpage::on_refreshBtn_clicked()
{
    QString id=ui->id_Edit->text();
    QString passwd=ui->pass_Edit->text();
    QString name=ui->name_Edit->text();
    int sexnum=ui->sexBox_2->currentIndex();
    QString sex;
    if(sexnum==0)sex="男";
    else sex="女";
    QString department=ui->dep_Edit->text();
    QString phone=ui->phone_Edit->text();
     QString address=ui->add_Edit->text();
     QSqlQuery test;

    //这里要好好想想异常判断，暂时先给这些
    if(id=="")
    {
        QMessageBox::warning(NULL,"Error","输入的学号不能为空！请重输");
        return;
    }
    QHash<QString,int> idHash;
    for (int i=0;i<dataTableModel->rowCount();i++)
    {
        QModelIndex idindex=dataTableModel->index(i,0);
        QString id1=dataTableModel->data(idindex).toString();
        idHash[id1]=1;
    }
    if (idHash.contains(id))
        {QMessageBox::warning(NULL,"Error","学号不能重复！请重输");return;}

    if (id.length()!=8) {QMessageBox::warning(NULL,"Error","学号须为8位数字！请重输");return;}
    for (int i=0;i<8;i++)
        if (id[i]<'0'||id[i]>'9') {QMessageBox::warning(NULL,"Error","学号须为8位数字！请重输");return;}

    if(passwd.length()<6||passwd.length()>15){
        QMessageBox::warning(this, "警告", "密码长度需为6-15位！请重输");
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
        QMessageBox::warning(NULL,"Error","输入姓名不能为空！！请重输");
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

    if (department=="") {QMessageBox::warning(NULL,"Error","学院不能为空！");return;}
    QString depsql=QString("select * from dep_table where department='%1'").arg(department);
    if (!test.exec(depsql))
    {
        QMessageBox::warning(NULL,"Error","不存在该学院！请重输");
        return;
    }

    //进行匹配
    std::regex r("^1(3|5|8)\\d{9}$");

    std::string userIdString =phone.toStdString();
    bool bValid=std::regex_match(userIdString,r);

    if(!bValid){
        QMessageBox::warning(NULL,"Error","输入的电话不合法！请重输");
        return;
    }

    if (address!="")
    {
        std::regex rega("^[\u4e00-\u9fa5]+省[\u4e00-\u9fa5]+市");
        std::string add=address.toStdString();
        bValid=std::regex_match(add,rega);
        if (!bValid){
                QMessageBox::warning(NULL,"警告","请输入合法住址！");
                return;
        }
    }

    QSqlQuery query;
    QString sql=QString("insert into student_table(sid,spasswd,sname,ssex,sdepartment,sphonenumber,saddress)values('%1','%2','%3','%4','%5','%6','%7')").arg(id).arg(passwd).arg(name).arg(sex).arg(department).arg(phone).arg(address);
    if (query.exec(sql))
        QMessageBox::information(NULL,"温馨提示","学生信息创建成功！");
    else QMessageBox::warning(NULL,"Error","学生信息创建失败！");
    shownew();
}

void studentpage::on_confirmBtn_clicked()
{
    QString id=ui->idEdit->text();
    if (id=="") {
        QMessageBox::warning(this, "警告", "请选择需要修改信息的学生！");
        return;
    }
    QString passwd=ui->passEdit->text();
    QString name=ui->nameEdit->text();
    int sexnum=ui->sexBox->currentIndex();
    QString sex;
    if(sexnum==0)sex="男";
    else sex="女";
    QString department=ui->depEdit->text();
    QString phone=ui->phoneEdit->text();
    QString address=ui->addEdit->text();

    if(passwd.length()<6||passwd.length()>15){
        QMessageBox::warning(this, "警告", "密码长度需为6-15位！请重输");
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
        QMessageBox::warning(NULL,"Error","输入姓名不能为空！！请重输");
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
    test.clear();
    if (department=="") {QMessageBox::warning(NULL,"Error","学院不能为空！");return;}
    QString depsql=QString("select * from dep_table where department='%1'").arg(department);
    if (!test.exec(depsql))
    {
        QMessageBox::warning(NULL,"Error","不存在该学院！请重输");
        return;
    }

    //进行匹配
    std::regex r("^1(3|5|8)\\d{9}$");

    std::string userIdString =phone.toStdString();
    bool bValid=std::regex_match(userIdString,r);

    if(!bValid){
        QMessageBox::warning(NULL,"Error","输入的电话不合法！请重输");
        return;
    }

    if (address!="")
    {
        std::regex rega("^[\u4e00-\u9fa5]+省[\u4e00-\u9fa5]+市");
        std::string add=address.toStdString();
        bValid=std::regex_match(add,rega);
        if (!bValid){
                QMessageBox::warning(NULL,"警告","请输入合法住址！");
                return;
        }
    }

    QSqlQuery querynw;
    QString sqlnw=QString("update student_table set sid='%1',spasswd='%2',sname='%3',ssex='%4',sdepartment='%5',sphonenumber='%6',saddress='%7' where sid='%8'").arg(id).arg(passwd).arg(name).arg(sex).arg(department).arg(phone).arg(address).arg(id);
    if(querynw.exec(sqlnw)) QMessageBox::information(NULL,"温馨提示","学生信息更改成功！");
    else QMessageBox::warning(NULL,"警告","学生信息更改失败！");
    this->dataTableModel->clear();
    shownew();
}

void studentpage::on_deleteBtn_clicked()
{
    QString deletename=ui->deleteEdit->text();
    if (deletename=="") {QMessageBox::warning(NULL,"Error","请选择输入学生id！");return;}


    //else
    //{
        deletename=ui->deleteEdit->text();
            QSqlQuery query;
            QString sql=QString("select * from student_table where sid='%1'").arg(deletename);
            query.exec(sql);
            if(query.first())
            {
                QMessageBox::StandardButton box;
                box = QMessageBox::question(this, "提示", "确定要删除吗?", QMessageBox::Yes|QMessageBox::No);
                if(box==QMessageBox::No)return;
                sql=QString("delete from student_table where sid='%1'").arg(deletename);
                query.exec(sql);
                QMessageBox::information(NULL,"温馨提示","删除成功！");
                qDebug()<<"删除成功";
            }
            else
            {
                QMessageBox::warning(NULL,"Error","输入信息有误！");
                qDebug()<<"删除失败";
            }
           query.clear();

        shownew();
    //}
}


void studentpage::on_pushButton_clicked()
{
    ui->searchbox->setCurrentIndex(0);
}


void studentpage::on_pushButton_2_clicked()
{
    ui->searchbox->setCurrentIndex(1);
}


void studentpage::on_pushButton_3_clicked()
{
    ui->searchbox->setCurrentIndex(2);
}


void studentpage::on_scoreBtn_clicked()
{
    QString id=scoreTableModel->data(scoreTableModel->index(0,0)).toString();
    for(int i=0;i<scoreTableModel->rowCount();i++)
    {
        QString course=scoreTableModel->data(scoreTableModel->index(i,1)).toString();

        QString scorestr=scoreTableModel->data(scoreTableModel->index(i,2)).toString();
        for (int i=0;i<scorestr.length();i++)
            if (scorestr[i]<'0'||scorestr[i]>'9')
            {QMessageBox::warning(NULL,"Error","请输入合法分数！");return;}

        double score=scoreTableModel->data(scoreTableModel->index(i,2)).toDouble();
        if (score<(int)0||score>(int)100) {QMessageBox::warning(NULL,"Error","请输入合法分数！");return;}

        QSqlQuery query;
        QString sql=QString("update score_table set sscore=%1 where sid='%2' and cid='%3'").arg(score).arg(id).arg(course);
        if(query.exec(sql))
        {
            qDebug()<<"成绩更新成功";
        }
        else
        {
            qDebug()<<"成绩更新失败";
        }
    }
     QSqlQuery query;
    this->scoreTableModel->clear();
    this->scoreTableModel->setHorizontalHeaderItem(0,new QStandardItem("学生id"));
    this->scoreTableModel->setHorizontalHeaderItem(1,new QStandardItem("课程id"));
    this->scoreTableModel->setHorizontalHeaderItem(2,new QStandardItem("分数"));
    QString sql=QString("select * from score_table where sid='%1'").arg(id);
    if(query.exec(sql))
    {
        qDebug()<<"成绩查询成功";
        int row=0;
        while(query.next())
        {
                this->scoreTableModel->setItem(row,0,new QStandardItem(query.value("sid").toString()));
                this->scoreTableModel->setItem(row,1,new QStandardItem(query.value("cid").toString()));
                this->scoreTableModel->setItem(row,2,new QStandardItem(query.value("sscore").toString()));
                row++;
        }
    }
    else
    {
        qDebug()<<"成绩查询失败";
        QMessageBox::warning(NULL,"查询失败","数据库没有该学生成绩信息！");
    }
}


void studentpage::on_quitBtn_clicked()
{
    this->close();
    LoginDialog *ld=new LoginDialog(NULL);
    ld->show();
}


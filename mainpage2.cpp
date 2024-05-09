#include "mainpage2.h"
#include "ui_mainpage2.h"
#include "dboperator.h"
#include "sign_page.h"
#include "logindialog.h"
#include "applylesson.h"
mainpage2::mainpage2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainpage2)
{
    ui->setupUi(this);

    this->setWindowTitle("课程管理");
    ui->topLabel->lower();
    ui->pushButton_2->setIcon(QIcon("image/add_1.png"));
    ui->pushButton_2->setLayoutDirection(Qt::LeftToRight);
    ui->pushButton_3->setIcon(QIcon("image/edit.png"));
    ui->pushButton_3->setLayoutDirection(Qt::LeftToRight);
    ui->pushButton_4->setIcon(QIcon("image/cancel.png"));
    ui->pushButton_4->setLayoutDirection(Qt::LeftToRight);
    ui->tostudentBtn->setIcon(QIcon("image/student.png"));
    ui->tostudentBtn->setLayoutDirection(Qt::LeftToRight);
    ui->toteacherBtn->setIcon(QIcon("image/teacher.png"));
    ui->toteacherBtn->setLayoutDirection(Qt::LeftToRight);
    ui->toannouceBtn->setIcon(QIcon("image/announce.png"));
    ui->toannouceBtn->setLayoutDirection(Qt::LeftToRight);

    ui->startBtn->setIcon(QIcon("image/assess.png"));
    ui->startBtn->setLayoutDirection(Qt::LeftToRight);
    ui->yesBtn->setIcon(QIcon("image/class.png"));
    ui->yesBtn->setLayoutDirection(Qt::LeftToRight);
    ui->scorelogBtn->setIcon(QIcon("image/SCORE_SET.png"));
    ui->scorelogBtn->setLayoutDirection(Qt::LeftToRight);
    ui->excelBtn->setIcon(QIcon("image/file2.png"));
    ui->excelBtn->setLayoutDirection(Qt::LeftToRight);
    ui->refreshBtn->setIcon(QIcon("image/right.png"));
    ui->refreshBtn->setLayoutDirection(Qt::RightToLeft);
    ui->confirmBtn->setIcon(QIcon("image/right.png"));
    ui->confirmBtn->setLayoutDirection(Qt::RightToLeft);
    ui->deleteBtn->setIcon(QIcon("image/wrong.png"));
    ui->deleteBtn->setLayoutDirection(Qt::RightToLeft);
    ui->deleterow->setIcon(QIcon("image/wrong.png"));
    ui->deleterow->setLayoutDirection(Qt::RightToLeft);

    QPixmap qp1("image/person.png");
    ui->picLabel->setPixmap(qp1);
    ui->picLabel->setScaledContents(true);
    ui->picLabel->show();

    //连接数据库
    this->myDataBase.DBOpen();
    //为表格模式指针指定内容
    this->dataTableModel=new QStandardItemModel();
    this->selection=new QItemSelectionModel(dataTableModel);
    //设置表格,现在测试的是课程表格
    this->setTabletInfo();
    this->getDatabaseInfo();
    //将设计好的表格样式装载到表格上
    ui->classTable->setModel(this->dataTableModel);
    //为tableview设置数据模型和选择模型
    ui->classTable->setSelectionModel(selection);
    //设置选中模式为整行选中
    ui->classTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    QObject::connect(this->dataTableModel,SIGNAL(dataChanged(const QModelIndex&,const QModelIndex &)),ui->classTable,SLOT(update()));
    //设置
    //设置默认表格为新增页面
    ui->control_page->setCurrentIndex(0);

    QString sql=QString("select * from dep_table");
    QSqlQuery query;
    query.exec(sql);
    while(query.next())
    {
        listData<<query.value("department").toString();
    }
    listData<<"是";
    listData<<"否";
    listData<<"公必";
    listData<<"公选";
    listData<<"专必";
    listData<<"专选";
    QString sql2=QString("select * from class_table");
    QSqlQuery query2;
    query2.exec(sql2);
    while(query2.next())
    {
        listData<<query2.value("tid").toString();
        listData<<query2.value("cid").toString();
    }
    QCompleter *m_pCompleter = new QCompleter(listData);
    m_pCompleter->setFilterMode(Qt::MatchContains);
    ui->key_edit->setCompleter(m_pCompleter);
}

mainpage2::~mainpage2()
{
    delete ui;
}
//查看课程设置表头
void mainpage2::setTabletInfo()
{
    //设置表头样式
    this->dataTableModel->setHorizontalHeaderItem(0,new QStandardItem("课程id"));
    this->dataTableModel->setHorizontalHeaderItem(1,new QStandardItem("课程名称"));
    this->dataTableModel->setHorizontalHeaderItem(2,new QStandardItem("课程性质"));
    this->dataTableModel->setHorizontalHeaderItem(3,new QStandardItem("学分"));
    this->dataTableModel->setHorizontalHeaderItem(4,new QStandardItem("开设院系"));
    this->dataTableModel->setHorizontalHeaderItem(5,new QStandardItem("教师学工号"));
    this->dataTableModel->setHorizontalHeaderItem(6,new QStandardItem("上课地点"));
    this->dataTableModel->setHorizontalHeaderItem(7,new QStandardItem("总课时"));
    this->dataTableModel->setHorizontalHeaderItem(8,new QStandardItem("课程人数"));
    this->dataTableModel->setHorizontalHeaderItem(9,new QStandardItem("已选人数"));
    this->dataTableModel->setHorizontalHeaderItem(10,new QStandardItem("是否开始评教"));
   this->dataTableModel->setHorizontalHeaderItem(11,new QStandardItem("考查方式"));
    this->dataTableModel->setHorizontalHeaderItem(12,new QStandardItem("是否开课"));

    //this->dataTableModel->setHorizontalHeaderItem(0,new QStandardItem(""));

    //设置列宽
    ui->classTable->setColumnWidth(0,100);
    ui->classTable->setColumnWidth(1,150);
    ui->classTable->setColumnWidth(2,70);
    ui->classTable->setColumnWidth(3,70);
    ui->classTable->setColumnWidth(4,100);
    ui->classTable->setColumnWidth(5,100);
    ui->classTable->setColumnWidth(6,100);
    ui->classTable->setColumnWidth(7,50);
    ui->classTable->setColumnWidth(8,70);
    ui->classTable->setColumnWidth(9,70);
    ui->classTable->setColumnWidth(10,80);
    ui->classTable->setColumnWidth(11,70);
    ui->classTable->setColumnWidth(12,70);

    //设置表格为只读（后续可以增加监听器和更新按钮）
    //ui->classTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //设置表格信息

}
void mainpage2::getDatabaseInfo()
{
    QSqlQuery sql;
    sql.prepare("select * from class_table");
    sql.exec();
    int row=0;
    while(sql.next())
    {
        this->dataTableModel->setItem(row,0,new QStandardItem(sql.value("cid").toString()));
        this->dataTableModel->setItem(row,1,new QStandardItem(sql.value("cname").toString()));
        this->dataTableModel->setItem(row,2,new QStandardItem(sql.value("cclassify").toString()));
        this->dataTableModel->setItem(row,3,new QStandardItem(sql.value("cscore").toString()));
        this->dataTableModel->setItem(row,4,new QStandardItem(sql.value("cdepartment").toString()));
        this->dataTableModel->setItem(row,5,new QStandardItem(sql.value("tid").toString()));
        this->dataTableModel->setItem(row,6,new QStandardItem(sql.value("clocation").toString()));
        this->dataTableModel->setItem(row,7,new QStandardItem(sql.value("ctime").toString()));
        this->dataTableModel->setItem(row,8,new QStandardItem(sql.value("ccapacity").toString()));

        QSqlQuery queryqq;
        queryqq.clear();
        QString sqlqq;
        sqlqq=QString("SELECT * FROM selectedlesson WHERE cid='%1'").arg(sql.value("cid").toString());
        queryqq.exec(sqlqq);
        int qq=0;
        while (queryqq.next())
            qq++;
        queryqq.clear();
        sqlqq=QString("UPDATE class_table SET ccur='%1' WHERE cid='%2'").arg(qq).arg(sql.value("cid").toString());
        queryqq.exec(sqlqq);

        this->dataTableModel->setItem(row,9,new QStandardItem(QString::number(qq)));
        int is_open=sql.value("is_open").toInt();
        QString is_op;
        if(is_open==0)is_op="否";
        else if(is_open==1)is_op="是";
        this->dataTableModel->setItem(row,10,new QStandardItem(is_op));
        this->dataTableModel->setItem(row,11,new QStandardItem(sql.value("kcfs").toString()));
        int is_apply=sql.value("is_apply").toInt();
        QString is_ap;
        if(is_apply==0)is_ap="否";
        else if(is_apply==1)is_ap="是";
        this->dataTableModel->setItem(row,12,new QStandardItem(is_ap));
        row++;
    }
    sql.clear();
}
void mainpage2::on_pushButton_2_clicked()
{
    ui->control_page->setCurrentIndex(0);
}

void mainpage2::on_pushButton_3_clicked()
{
    ui->control_page->setCurrentIndex(1);
}

void mainpage2::on_pushButton_4_clicked()
{
    ui->control_page->setCurrentIndex(2);
}

void mainpage2::on_refreshBtn_clicked()
{
    //首先要弹出提示框-----------如果信息都符合要求，，那么弹出确认框，，如果有非正常信息，应该弹出警告框
    //警告框返回原来页面---也就是不修改，但是更新后需要更新数据库并且，重绘该页面
    QString id=ui->id_Edit->text();
    QString name=ui->name_Edit->text();
    int cla=ui->classifyBox_2->currentIndex();
    QString classify;
    if(cla==0)
    {
        classify="公必";
    }
    else if(cla==1)
    {
        classify="公选";
    }
    else if(cla==2)
    {
        classify="专必";
    }
    else if(cla==3)
    {
        classify="专选";
    }
    int score=ui->sco_Edit->text().toInt();
    QString department=ui->depa_Edit->text();
    QString teacher=ui->tea_Edit->text();
    QString location=ui->loc_Edit->text();
    QString kcfs;
    int kc=ui->kcfsBox_2->currentIndex();
    if(kc==0)
    {
        kcfs="论文考查";
    }
    else if(kc==1)
    {
        kcfs="开卷考试";
    }
    else if(kc==2)
    {
        kcfs="闭卷考试";
    }
    int time=ui->time_Edit->text().toInt();
    int capacity=ui->cap_Edit->text().toInt();
    int cur=0;
    int is_open=0;
    int is_apply=0;

    if(id=="")
    {
        QMessageBox::warning(NULL,"Error","输入的课程id不能为空！请重输");
        return;
    }
    if(name=="")
    {
        QMessageBox::warning(NULL,"Error","输入的课程名称不能为空！请重输");
        return;
    }
    if(teacher=="")
    {
        QMessageBox::warning(NULL,"Error","输入的课程教师不能为空！请重输");
        return;
    }
    if(location=="")
    {
        QMessageBox::warning(NULL,"Error","输入的课程地点不能为空！请重输");
        return;
    }

    QSqlQuery test;
    test.exec(QString("select * from class_table where cid='%1'").arg(id));
    if(test.next()){
        QMessageBox::warning(NULL,"Error","该课程id已存在，请重输！");
        return;
    }

    if (id.length()!=4) {
        QMessageBox::warning(NULL,"Error","课程id须为4位数字，请重输！");
        return;
    }
    for (int i=0;i<4;i++)
    {
        if (id[i]>='0'&&id[i]<='9') continue;
        QMessageBox::warning(NULL,"Error","课程id须为4位数字，请重输！");
        return;
    }

    test.clear();
    test.exec(QString("select * from dep_table where dep_table.department='%1'").arg(department));
    if(!test.next()){
        QMessageBox::warning(NULL,"Error","不存在该学院，请重输！");
        return;
    }

    test.clear();
    test.exec(QString("select * from teacher_table where tid='%1'").arg(teacher));
    if(!test.next()){
        QMessageBox::warning(NULL,"Error","不存在该教师，请重输！");
        return;
    }

    if (location.length()!=4){
        QMessageBox::warning(NULL,"Error","请输入合法上课地点！");
        return;
    }
    if (location[0]<'A'||location[0]>'F'){
        QMessageBox::warning(NULL,"Error","请输入合法上课地点！");
        return;
    }
    if (location[1]<'1'||location[1]>'6'){
        QMessageBox::warning(NULL,"Error","请输入合法上课地点！");
        return;
    }
    if (location[2]<'0'||location[2]>'1'){
        QMessageBox::warning(NULL,"Error","请输入合法上课地点！");
        return;
    }
    if ((location[2]=='0'&&location[3]=='0')||(location[2]=='1'&&location[3]>'2')){
        QMessageBox::warning(NULL,"Error","请输入合法上课地点！");
        return;
    }

    //代码的异常判断块
    if(time<=0)
    {
        QMessageBox::warning(NULL,"Error","输入的课程课时须大于0！请重输");
        return;
    }
    else if(time>=200)
    {
        QMessageBox::warning(NULL,"Error","输入的课程课时不能大于200！请重输");
        return;
    }
    else if(score<=0)
    {
        QMessageBox::warning(NULL,"Error","输入的学分须大于0！请重输");
        return;
    }
    else if(score>8)
    {
        QMessageBox::warning(NULL,"Error","输入的学分不能大于8！请重输");
        return;
    }
    else if(capacity<20)
    {
        QMessageBox::warning(NULL,"Error","输入的课程容量不能小于20！请重输");
        return;
    }
    else if(capacity>200)
    {
        QMessageBox::warning(NULL,"Error","输入的课程容量不能大于200！请重输");
        return;
    }
    else if(cur<0)
    {
        QMessageBox::warning(NULL,"Error","输入的选课人数不能小于0！请重输");
        return;
    }
    else if(cur>capacity)
    {
        QMessageBox::warning(NULL,"Error","输入的选课人数不能大于课程容量！请重输");
        return;
    }
    else
    {
        QSqlQuery query;
        QString sql=QString("insert into class_table(cid,cname,cclassify,cscore,cdepartment,tid,clocation,ctime,ccapacity,ccur,is_open,kcfs,is_apply)values('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13')").arg(id).arg(name).arg(classify).arg(score).arg(department).arg(teacher).arg(location).arg(time).arg(capacity).arg(cur).arg(is_open).arg(kcfs).arg(is_apply);
        qDebug()<<"插入class_table："<<sql;
        if(query.exec(sql))
        {
            qDebug()<<"创建课程成功";
            QMessageBox::information(NULL,"温馨提示","创建课程成功！");
        }
        else
        {
            qDebug()<<"创建课程失败";
            QMessageBox::warning(NULL,"Error","创建课程失败！");
        }
        query.clear();
        sql=QString("insert into arr_table(cid,tid,clocation)values('%1','%2','%3')").arg(id).arg(teacher).arg(location);
        qDebug()<<"添加arr的sql："<<sql;
        query.exec(sql);
    }
    shownew();
}

void mainpage2::on_deleteBtn_clicked()
{
    QString tmpname=ui->delete_Edit->text();
    if (tmpname=="") {QMessageBox::warning(NULL,"Error","请输入需删除的课程信息！");return;}

    //else
    //{
        int index=ui->comboBox_delete->currentIndex();
        //读取删除的字段名
        QString deletename=ui->delete_Edit->text();
        //按照课程id
        if(index==0)
        {
            QSqlQuery query;
            QString sql=QString("SELECT * from class_table where cid='%1'").arg(deletename);
            query.exec(sql);
            if(query.next())
            {
                QMessageBox::StandardButton box;
                box = QMessageBox::question(this, "提示", "确定要删除吗?", QMessageBox::Yes|QMessageBox::No);
                if(box==QMessageBox::No)return;
                sql=QString("delete from class_table where cid='%1'").arg(deletename);
                query.exec(sql);
                QMessageBox::information(NULL,"温馨提示","删除成功！");
            }
            else
            {
                QMessageBox::warning(NULL,"Error","输入信息有误！");
                return;
            }
           query.clear();
        }
        //按照课程名称
        else if(index==1)
        {
            QSqlQuery query;
            QString sql=QString("SELECT * from class_table where cname='%1'").arg(deletename);

            query.exec(sql);
            if(query.next())
            {
                QMessageBox::StandardButton box;
                box = QMessageBox::question(this, "提示", "确定要删除吗?", QMessageBox::Yes|QMessageBox::No);
                if(box==QMessageBox::No)return;
                sql=QString("delete from class_table where cname='%1'").arg(deletename);
                QMessageBox::information(NULL,"温馨提示","删除成功！");
            }
            else
            {
                QMessageBox::warning(NULL,"Error","输入信息有误！");
                return;
            }
            query.clear();
        }
        shownew();
    //}
}

void mainpage2::shownew()
{
    this->dataTableModel->clear();
    this->setTabletInfo();
    //将设计好的表格样式装载到表格上
    ui->classTable->setModel(this->dataTableModel);
    //为tableview设置数据模型和选择模型
    QSqlQuery query;
    QString sql=QString("select * from class_table ");
    if(query.exec(sql))
    {
        qDebug()<<"查询成功";
        int row=0;
        while(query.next())
        {
            this->dataTableModel->setItem(row,0,new QStandardItem(query.value("cid").toString()));
            this->dataTableModel->setItem(row,1,new QStandardItem(query.value("cname").toString()));
            this->dataTableModel->setItem(row,2,new QStandardItem(query.value("cclassify").toString()));
            this->dataTableModel->setItem(row,3,new QStandardItem(query.value("cscore").toString()));
            this->dataTableModel->setItem(row,4,new QStandardItem(query.value("cdepartment").toString()));
            this->dataTableModel->setItem(row,5,new QStandardItem(query.value("tid").toString()));
            this->dataTableModel->setItem(row,6,new QStandardItem(query.value("clocation").toString()));
            this->dataTableModel->setItem(row,7,new QStandardItem(query.value("ctime").toString()));
            this->dataTableModel->setItem(row,8,new QStandardItem(query.value("ccapacity").toString()));
            this->dataTableModel->setItem(row,9,new QStandardItem(query.value("ccur").toString()));
            int is_open=query.value("is_open").toInt();
            QString is_op;
            if(is_open==0)is_op="否";
            else if(is_open==1)is_op="是";
            this->dataTableModel->setItem(row,10,new QStandardItem(is_op));
            this->dataTableModel->setItem(row,11,new QStandardItem(query.value("kcfs").toString()));
            int is_apply=query.value("is_apply").toInt();
            QString is_ap;
            if(is_apply==0)is_ap="否";
            else if(is_apply==1)is_ap="是";
            this->dataTableModel->setItem(row,12,new QStandardItem(is_ap));
            row++;
        }
    }
    else
    {
        qDebug()<<"查询失败";
    }
    query.clear();
}
void mainpage2::on_searchBtn_clicked()
{
    int index=ui->searchBox->currentIndex();
    //读取查询的内容
    QString searchname=ui->key_edit->text();
    qDebug()<<searchname;
    this->dataTableModel->clear();
    this->setTabletInfo();
    //将设计好的表格样式装载到表格上
    ui->classTable->setModel(this->dataTableModel);
    //按照课程性质
    if(index==0)
    {
        QSqlQuery query;
        QString sql=QString("select * from class_table where cclassify='%1'").arg(searchname);
        if(query.exec(sql))
        {
            qDebug()<<"查询成功";
            int row=0;
            while(query.next())
            {
                this->dataTableModel->setItem(row,0,new QStandardItem(query.value("cid").toString()));
                this->dataTableModel->setItem(row,1,new QStandardItem(query.value("cname").toString()));
                this->dataTableModel->setItem(row,2,new QStandardItem(query.value("cclassify").toString()));
                this->dataTableModel->setItem(row,3,new QStandardItem(query.value("cscore").toString()));
                this->dataTableModel->setItem(row,4,new QStandardItem(query.value("cdepartment").toString()));
                this->dataTableModel->setItem(row,5,new QStandardItem(query.value("tid").toString()));
                this->dataTableModel->setItem(row,6,new QStandardItem(query.value("clocation").toString()));
                this->dataTableModel->setItem(row,7,new QStandardItem(query.value("ctime").toString()));
                this->dataTableModel->setItem(row,8,new QStandardItem(query.value("ccapacity").toString()));
                this->dataTableModel->setItem(row,9,new QStandardItem(query.value("ccur").toString()));
                int is_open=query.value("is_open").toInt();
                QString is_op;
                if(is_open==0)is_op="否";
                else if(is_open==1)is_op="是";
                this->dataTableModel->setItem(row,10,new QStandardItem(is_op));
                this->dataTableModel->setItem(row,11,new QStandardItem(query.value("kcfs").toString()));
                int is_apply=query.value("is_apply").toInt();
                QString is_ap;
                if(is_apply==0)is_ap="否";
                else if(is_apply==1)is_ap="是";
                this->dataTableModel->setItem(row,12,new QStandardItem(is_ap));
                row++;
            }
        }
        else
        {
            QMessageBox::warning(NULL,"查询失败","数据库没有该信息");
        }
        query.clear();
    }
    //按照开设院系
    else if(index==1)
    {
        QSqlQuery query;
        QString sql=QString("select * from class_table where cdepartment='%1'").arg(searchname);
        if(query.exec(sql))
        {
            qDebug()<<"查询成功";
            int row=0;
            while(query.next())
            {
                this->dataTableModel->setItem(row,0,new QStandardItem(query.value("cid").toString()));
                this->dataTableModel->setItem(row,1,new QStandardItem(query.value("cname").toString()));
                this->dataTableModel->setItem(row,2,new QStandardItem(query.value("cclassify").toString()));
                this->dataTableModel->setItem(row,3,new QStandardItem(query.value("cscore").toString()));
                this->dataTableModel->setItem(row,4,new QStandardItem(query.value("cdepartment").toString()));
                this->dataTableModel->setItem(row,5,new QStandardItem(query.value("tid").toString()));
                this->dataTableModel->setItem(row,6,new QStandardItem(query.value("clocation").toString()));
                this->dataTableModel->setItem(row,7,new QStandardItem(query.value("ctime").toString()));
                this->dataTableModel->setItem(row,8,new QStandardItem(query.value("ccapacity").toString()));
                this->dataTableModel->setItem(row,9,new QStandardItem(query.value("ccur").toString()));
                int is_open=query.value("is_open").toInt();
                QString is_op;
                if(is_open==0)is_op="否";
                else if(is_open==1)is_op="是";
                this->dataTableModel->setItem(row,10,new QStandardItem(is_op));
                this->dataTableModel->setItem(row,11,new QStandardItem(query.value("kcfs").toString()));
                int is_apply=query.value("is_apply").toInt();
                QString is_ap;
                if(is_apply==0)is_ap="否";
                else if(is_apply==1)is_ap="是";
                this->dataTableModel->setItem(row,12,new QStandardItem(is_ap));

                row++;
            }
        }
        else
        {
            QMessageBox::warning(NULL,"查询失败","数据库没有该信息");
        }
        query.clear();
    }
    //按照教师id
    else if(index==2)
    {
        QSqlQuery query;
        QString sql=QString("select * from class_table where tid='%1'").arg(searchname);
        if(query.exec(sql))
        {
            qDebug()<<"查询成功";
            int row=0;
            while(query.next())
            {
                this->dataTableModel->setItem(row,0,new QStandardItem(query.value("cid").toString()));
                this->dataTableModel->setItem(row,1,new QStandardItem(query.value("cname").toString()));
                this->dataTableModel->setItem(row,2,new QStandardItem(query.value("cclassify").toString()));
                this->dataTableModel->setItem(row,3,new QStandardItem(query.value("cscore").toString()));
                this->dataTableModel->setItem(row,4,new QStandardItem(query.value("cdepartment").toString()));
                this->dataTableModel->setItem(row,5,new QStandardItem(query.value("tid").toString()));
                this->dataTableModel->setItem(row,6,new QStandardItem(query.value("clocation").toString()));
                this->dataTableModel->setItem(row,7,new QStandardItem(query.value("ctime").toString()));
                this->dataTableModel->setItem(row,8,new QStandardItem(query.value("ccapacity").toString()));
                this->dataTableModel->setItem(row,9,new QStandardItem(query.value("ccur").toString()));
                int is_open=query.value("is_open").toInt();
                QString is_op;
                if(is_open==0)is_op="否";
                else if(is_open==1)is_op="是";
                this->dataTableModel->setItem(row,10,new QStandardItem(is_op));
                this->dataTableModel->setItem(row,11,new QStandardItem(query.value("kcfs").toString()));
                int is_apply=query.value("is_apply").toInt();
                QString is_ap;
                if(is_apply==0)is_ap="否";
                else if(is_apply==1)is_ap="是";
                this->dataTableModel->setItem(row,12,new QStandardItem(is_ap));

                row++;
            }
        }
        else
        {
            QMessageBox::warning(NULL,"查询失败","数据库没有该信息");
        }
        query.clear();
    }
    //按照课程id
    else if(index==3)
    {
        QSqlQuery query;
        QString sql=QString("select * from class_table where cid='%1'").arg(searchname);
        if(query.exec(sql))
        {
            qDebug()<<"查询成功";
            int row=0;
            while(query.next())
            {
                this->dataTableModel->setItem(row,0,new QStandardItem(query.value("cid").toString()));
                this->dataTableModel->setItem(row,1,new QStandardItem(query.value("cname").toString()));
                this->dataTableModel->setItem(row,2,new QStandardItem(query.value("cclassify").toString()));
                this->dataTableModel->setItem(row,3,new QStandardItem(query.value("cscore").toString()));
                this->dataTableModel->setItem(row,4,new QStandardItem(query.value("cdepartment").toString()));
                this->dataTableModel->setItem(row,5,new QStandardItem(query.value("tid").toString()));
                this->dataTableModel->setItem(row,6,new QStandardItem(query.value("clocation").toString()));
                this->dataTableModel->setItem(row,7,new QStandardItem(query.value("ctime").toString()));
                this->dataTableModel->setItem(row,8,new QStandardItem(query.value("ccapacity").toString()));
                this->dataTableModel->setItem(row,9,new QStandardItem(query.value("ccur").toString()));
                int is_open=query.value("is_open").toInt();
                QString is_op;
                if(is_open==0)is_op="否";
                else if(is_open==1)is_op="是";
                this->dataTableModel->setItem(row,10,new QStandardItem(is_op));
                this->dataTableModel->setItem(row,11,new QStandardItem(query.value("kcfs").toString()));
                int is_apply=query.value("is_apply").toInt();
                QString is_ap;
                if(is_apply==0)is_ap="否";
                else if(is_apply==1)is_ap="是";
                this->dataTableModel->setItem(row,12,new QStandardItem(is_ap));

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
    else if(index==4)
    {
        QSqlQuery query;
        int is=0;
        if(searchname=="是")is=1;
        else if(searchname=="否")is=0;
        QString sql=QString("select * from class_table where is_apply='%1'").arg(is);
        if(query.exec(sql))
        {

           qDebug()<<"查询成功";
           int row=0;
           while(query.next())
           {
                this->dataTableModel->setItem(row,0,new QStandardItem(query.value("cid").toString()));
                this->dataTableModel->setItem(row,1,new QStandardItem(query.value("cname").toString()));
                this->dataTableModel->setItem(row,2,new QStandardItem(query.value("cclassify").toString()));
                this->dataTableModel->setItem(row,3,new QStandardItem(query.value("cscore").toString()));
                this->dataTableModel->setItem(row,4,new QStandardItem(query.value("cdepartment").toString()));
                this->dataTableModel->setItem(row,5,new QStandardItem(query.value("tid").toString()));
                this->dataTableModel->setItem(row,6,new QStandardItem(query.value("clocation").toString()));
                this->dataTableModel->setItem(row,7,new QStandardItem(query.value("ctime").toString()));
                this->dataTableModel->setItem(row,8,new QStandardItem(query.value("ccapacity").toString()));
                this->dataTableModel->setItem(row,9,new QStandardItem(query.value("ccur").toString()));
                int is_open=query.value("is_open").toInt();
                QString is_op;
                if(is_open==0)is_op="否";
                else if(is_open==1)is_op="是";
                this->dataTableModel->setItem(row,10,new QStandardItem(is_op));
                this->dataTableModel->setItem(row,11,new QStandardItem(query.value("kcfs").toString()));
                int is_apply=query.value("is_apply").toInt();
                QString is_ap;
                if(is_apply==0)is_ap="否";
                else if(is_apply==1)is_ap="是";
                this->dataTableModel->setItem(row,12,new QStandardItem(is_ap));

                row++;
           }
        }
        else
        {
           QMessageBox::warning(NULL,"查询失败","数据库没有该信息");
        }
        query.clear();
    }
    else if(index==5)
    {
        QSqlQuery query;
        int is=0;
        if(searchname=="是")is=1;
        else if(searchname=="否")is=0;
       QString sql=QString("select * from class_table where is_open='%1'").arg(is);
        if(query.exec(sql))
        {
           qDebug()<<"查询成功";
           int row=0;
           while(query.next())
           {
                this->dataTableModel->setItem(row,0,new QStandardItem(query.value("cid").toString()));
                this->dataTableModel->setItem(row,1,new QStandardItem(query.value("cname").toString()));
                this->dataTableModel->setItem(row,2,new QStandardItem(query.value("cclassify").toString()));
                this->dataTableModel->setItem(row,3,new QStandardItem(query.value("cscore").toString()));
                this->dataTableModel->setItem(row,4,new QStandardItem(query.value("cdepartment").toString()));
                this->dataTableModel->setItem(row,5,new QStandardItem(query.value("tid").toString()));
                this->dataTableModel->setItem(row,6,new QStandardItem(query.value("clocation").toString()));
                this->dataTableModel->setItem(row,7,new QStandardItem(query.value("ctime").toString()));
                this->dataTableModel->setItem(row,8,new QStandardItem(query.value("ccapacity").toString()));
                this->dataTableModel->setItem(row,9,new QStandardItem(query.value("ccur").toString()));
                int is_open=query.value("is_open").toInt();
                QString is_op;
                if(is_open==0)is_op="否";
                else if(is_open==1)is_op="是";
                this->dataTableModel->setItem(row,10,new QStandardItem(is_op));
                this->dataTableModel->setItem(row,11,new QStandardItem(query.value("kcfs").toString()));
                int is_apply=query.value("is_apply").toInt();
                QString is_ap;
                if(is_apply==0)is_ap="否";
                else if(is_apply==1)is_ap="是";
                this->dataTableModel->setItem(row,12,new QStandardItem(is_ap));

                row++;
           }
        }
        else
        {
           QMessageBox::warning(NULL,"查询失败","数据库没有该信息");
        }
        query.clear();
    }
        else
    {
        ui->key_edit->clear();
        shownew();
    }
}

void mainpage2::on_tostudentBtn_clicked()
{
    studentpage* w=new studentpage();
    w->show();
    this->close();
}

void mainpage2::on_toteacherBtn_clicked()
{
    teacherpage* w=new teacherpage();
    w->show();
    this->close();
}


void mainpage2::on_toannouceBtn_clicked()
{
    announcepage *w=new announcepage();
    w->show();
    this->close();
}


void mainpage2::on_classTable_clicked(const QModelIndex &index)
{
    //数据的行和列都是从0开始计数
    int row=ui->classTable->currentIndex().row();
    qDebug()<<row;
    QModelIndex index1=dataTableModel->index(row,0);
    QModelIndex index2=dataTableModel->index(row,1);
    QModelIndex index3=dataTableModel->index(row,2);
    QModelIndex index4=dataTableModel->index(row,3);
    QModelIndex index5=dataTableModel->index(row,4);
    QModelIndex index6=dataTableModel->index(row,5);
    QModelIndex index7=dataTableModel->index(row,6);
    QModelIndex index8=dataTableModel->index(row,7);
    QModelIndex index9=dataTableModel->index(row,8);
    QModelIndex index10=dataTableModel->index(row,9);
    QModelIndex index11=dataTableModel->index(row,10);
    QModelIndex index12=dataTableModel->index(row,11);
    QModelIndex index13=dataTableModel->index(row,12);
    QString id=dataTableModel->data(index1).toString();
    qDebug()<<id;
    QString name=dataTableModel->data(index2).toString();
    QString classify=dataTableModel->data(index3).toString();
    QString score=dataTableModel->data(index4).toString();
    QString department=dataTableModel->data(index5).toString();
    QString teacher=dataTableModel->data(index6).toString();
    QString location=dataTableModel->data(index7).toString();
    QString time=dataTableModel->data(index8).toString();
    QString capacity=dataTableModel->data(index9).toString();
    QString cur=dataTableModel->data(index10).toString();

    QString kcfs=dataTableModel->data(index12).toString();

    ui->control_page->setCurrentIndex(1);
    ui->lineEdit->setText(id);
    ui->lineEdit_2->setText(name);
    if(classify=="公必")
    {
        ui->classifyBox->setCurrentIndex(0);
    }
    else if(classify=="公选")
    {
        ui->classifyBox->setCurrentIndex(1);
    }
    else if(classify=="专必")
    {
        ui->classifyBox->setCurrentIndex(2);
    }
    else if(classify=="专选")
    {
        ui->classifyBox->setCurrentIndex(3);
    }
    ui->lineEdit_4->setText(score);
    ui->lineEdit_5->setText(department);
    ui->lineEdit_6->setText(teacher);
    ui->lineEdit_7->setText(location);
    ui->lineEdit_8->setText(time);
    ui->lineEdit_9->setText(capacity);
    ui->lineEdit_10->setText(cur);
    if(kcfs=="论文考查")
        ui->kcfsBox->setCurrentIndex(0);
    else if(kcfs=="开卷考试")
        {
        ui->kcfsBox->setCurrentIndex(1);
    }
    else if(kcfs=="闭卷考试")
    {
        ui->kcfsBox->setCurrentIndex(2);
    }

}
void mainpage2::on_confirmBtn_clicked()
{
    QString id=ui->lineEdit->text();
    QString name=ui->lineEdit_2->text();
    int cla=ui->classifyBox->currentIndex();
    QString classify;
    if(cla==0)
    {
        classify="公必";
    }
    else if(cla==1)
    {
        classify="公选";
    }
    else if(cla==2)
    {
        classify="专必";
    }
    else if(cla==3)
    {
        classify="专选";
    }
    int score=ui->lineEdit_4->text().toInt();
    QString dep=ui->lineEdit_5->text();
    QString teacher=ui->lineEdit_6->text();
    QString location=ui->lineEdit_7->text();
    int time=ui->lineEdit_8->text().toInt();
    int capacity=ui->lineEdit_9->text().toInt();
    int cur=ui->lineEdit_10->text().toInt();
    QString kcfs;
    int kc=ui->kcfsBox->currentIndex();

    if(kc==0)
    {
        kcfs="论文考察";
    }
    else if(kc==1)
    {
        kcfs="开卷考试";
    }
    else if(kc==2)
    {
        kcfs="闭卷考试";
    }
    //代码的异常判断块
    if(name=="")
    {
        QMessageBox::warning(NULL,"Error","输入的课程名称不能为空！请重输");
        return;
    }
    if(teacher=="")
    {
           QMessageBox::warning(NULL,"Error","输入的课程教师不能为空！请重输");
           return;
    }
    QSqlQuery test;
    test.exec(QString("select * from dep_table where dep_table.department='%1'").arg(dep));
    if(!test.next()){
        QMessageBox::warning(NULL,"Error","不存在该学院！请重输");
        return;
    }
    test.clear();
    test.exec(QString("select * from teacher_table where tid='%1'").arg(teacher));
    if(!test.next()){
        QMessageBox::warning(NULL,"Error","不存在该教师，请重输！");
        return;
    }
    if(location=="")
    {
           QMessageBox::warning(NULL,"Error","输入的上课地点不能为空！请重输");
           return;
    }
    if (location.length()!=4){
        QMessageBox::warning(NULL,"Error","请输入合法上课地点！");
        return;
    }
    if (location[0]<'A'||location[0]>'F'){
        QMessageBox::warning(NULL,"Error","请输入合法上课地点！");
        return;
    }
    if (location[1]<'1'||location[1]>'6'){
        QMessageBox::warning(NULL,"Error","请输入合法上课地点！");
        return;
    }
    if (location[2]<'0'||location[2]>'1'){
        QMessageBox::warning(NULL,"Error","请输入合法上课地点！");
        return;
    }
    if ((location[2]=='0'&&location[3]=='0')||(location[2]=='1'&&location[3]>'2')){
        QMessageBox::warning(NULL,"Error","请输入合法上课地点！");
        return;
    }
    if(time<=0)
    {
           QMessageBox::warning(NULL,"Error","输入的课程课时须大于0！");
           return;
    }
    if(time>=200)
    {
           QMessageBox::warning(NULL,"Error","输入的课程课时不得多于200！");
           return;
    }
    if(score<=0)
    {
        QMessageBox::warning(NULL,"Error","输入的学分须大于0！");
        return;
    }
    if(score>8)
    {
        QMessageBox::warning(NULL,"Error","输入的学分不得多于8！");
        return;
    }
    if(capacity<20)
    {
        QMessageBox::warning(NULL,"Error","输入的课程容量不得小于20！");
        return;
    }
    if(capacity>200)
    {
        QMessageBox::warning(NULL,"Error","输入的课程容量不得大于200！");
        return;
    }
    else if(cur<0)
    {
        QMessageBox::warning(NULL,"Error","输入的选课人数不能小于0！");
        return;
    }
    if(cur>capacity)
    {
        QMessageBox::warning(NULL,"Error","输入的选课人数不能大于课程容量！");
        return;
    }

    QSqlQuery query;

    QString sql=QString("update class_table set cid='%1',cname='%2',cclassify='%3',cscore='%4',cdepartment='%5',tid='%6',clocation='%7',ctime='%8',ccapacity='%9',ccur='%10',kcfs='%11' where cid='%12'").arg(id).arg(name).arg(classify).arg(score).arg(dep).arg(teacher).arg(location).arg(time).arg(capacity).arg(cur).arg(kcfs).arg(id);
    if(query.exec(sql))
        QMessageBox::information(NULL,"温馨提示","更改课程成功");
    else
        QMessageBox::warning(NULL,"更改失败","更改数据库失败");
    this->dataTableModel->clear();
    shownew();
}


void mainpage2::on_deleterow_clicked()
{
    int row=ui->classTable->currentIndex().row();
     qDebug()<<row;
    QModelIndex index1=dataTableModel->index(row,0);
    if(!index1.isValid())
    {
        QMessageBox:: QMessageBox::warning(NULL, "Error", "没有选中行");
        return;
    }
    QMessageBox::StandardButton box;
    box = QMessageBox::question(this, "提示", "确定要删除这一行的内容吗?", QMessageBox::Yes|QMessageBox::No);
    if(box==QMessageBox::No)return;
    else
    {
        QString deletename=dataTableModel->data(index1).toString();

        //按照课程id
         QSqlQuery query;
         QString sql=QString("delete from class_table where cid='%1'").arg(deletename);
            if(query.exec(sql))
            {
                qDebug()<<"删除成功";
            }
            else
            {
                QMessageBox::warning(NULL,"删除失败","删除数据库信息失败");
            }
           query.clear();
        shownew();
    }

}
void mainpage2::on_excelBtn_clicked()
{
    QString filepath = QFileDialog::getSaveFileName(this, tr("Save as..."),
       QString(), tr("EXCEL files (*.xls *.xlsx)"));

    int row =dataTableModel->rowCount();
    int col = dataTableModel->columnCount();
    QList<QString> list;
    //添加列标题
    QString HeaderRow;
    for (int i = 0; i<col; i++)
    {
        HeaderRow.append(dataTableModel->horizontalHeaderItem(i)->text() + "\t");
    }
    list.push_back(HeaderRow);
    for (int i = 0; i<row; i++)
    {
        QString rowStr = "";
        for (int j = 0; j<col; j++)
        {
                rowStr += dataTableModel->item(i, j)->text() + "\t";
        }
        list.push_back(rowStr);
    }
    //将表格内容添加到富文本中
    QTextEdit textEdit;
    for (int i = 0; i<list.size(); i++)
    {
        textEdit.append(list.at(i));
    }
    //写入文件中
    QFile file(filepath);
    if (file.open(QFile::WriteOnly | QIODevice::Text))
    {
        QTextStream ts(&file);
        ts << textEdit.document()->toPlainText();
        file.close();
    }
}
void mainpage2::on_scorelogBtn_clicked()
{
    int row=ui->classTable->currentIndex().row();
    qDebug()<<row;
    QModelIndex index1=dataTableModel->index(row,0);
    if(!index1.isValid())
    {
        QMessageBox:: QMessageBox::warning(NULL, "Error", "没有选中行");
        return;
    }
    QString input=dataTableModel->data(index1).toString();
    scoreinput=new ScoreInputDialog();
    scoreinput->selectedLessonID=input;
    qDebug()<<"选中的课程id为"<<scoreinput->selectedLessonID;
    scoreinput->setmodel();
    scoreinput->show();
}

void mainpage2::on_yesBtn_clicked()
{
    int row=ui->classTable->currentIndex().row();
    qDebug()<<row;
    QModelIndex index1=dataTableModel->index(row,0);
    if(!index1.isValid())
    {
        QMessageBox:: QMessageBox::warning(NULL, "Error", "没有选中行");
        return;
    }
    QModelIndex index2=dataTableModel->index(row,12);
    QString is_apply=dataTableModel->data(index2).toString();
    if(is_apply=="是")
    {
        QMessageBox:: QMessageBox::warning(NULL, "Error", "这门课程已经开课");
        return;
    }

    applylesson *al=new applylesson(NULL,dataTableModel->data(index1).toString());
    al->show();
    //connect(newpage,&news_ope::closed,this,&announcepage::gets);
    connect(al,&applylesson::closed,this,&mainpage2::gets);
}
void mainpage2::gets()
{
    shownew();
}


void mainpage2::on_startBtn_clicked()
{
    int row=ui->classTable->currentIndex().row();
     qDebug()<<row;
    QModelIndex index1=dataTableModel->index(row,0);
    if(!index1.isValid())
    {
        QMessageBox:: QMessageBox::warning(NULL, "Error", "没有选中行");
        return;
    }
    QModelIndex index2=dataTableModel->index(row,10);
    QModelIndex indexa=dataTableModel->index(row,12);
    QString is_apply=dataTableModel->data(indexa).toString();
    if(is_apply=="否")
    {
        QMessageBox:: QMessageBox::warning(NULL, "Error", "这门课程尚未开课！");
        return;
    }

    QString is_open=dataTableModel->data(index2).toString();
    if(is_open=="是")
    {
        QMessageBox:: QMessageBox::warning(NULL, "Error", "这门课程已经开始评教！");
        return;
    }
    QMessageBox::StandardButton box;
    box = QMessageBox::question(this, "提示", "确定要开始这门课程的评教吗?", QMessageBox::Yes|QMessageBox::No);
    if(box==QMessageBox::No)return;
    else
    {
        QString openname=dataTableModel->data(index1).toString();
        //按照课程id
         QSqlQuery query;
        QString sql=QString("update class_table set is_open=1 where cid='%1'").arg(openname);
        if (query.exec(sql))
            {QMessageBox::information(NULL,"温馨提示","设置成功！");qDebug()<<"开课成功";}
        else QMessageBox::warning(NULL,"开课失败","修改数据库信息失败");
        query.clear();
        shownew();
    }
}


void mainpage2::on_quitBtn_clicked()
{
    this->close();
    LoginDialog *ld=new LoginDialog(NULL);
    ld->show();
}


#include "announcepage.h"
#include "ui_announcepage.h"
#include"news_ope.h"
announcepage::announcepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::announcepage)
{
    ui->setupUi(this);
    //连接数据库
    this->myDataBase.DBOpen();
    //设置表格,现在测试的是课程表格
    this->setlistinfo();
    //设置默认表格为新增页面
    ui->tabWidget->setCurrentIndex(0);
    QString sql=QString("select * from news_table");
    QSqlQuery query;
    query.exec(sql);
    while(query.next())
    {
        listData<<query.value("news_title").toString();
    }
    QCompleter *m_pCompleter = new QCompleter(listData);
    m_pCompleter->setFilterMode(Qt::MatchContains);
    ui->searchEdit->setCompleter(m_pCompleter);
}
void announcepage::gets()
{
    qDebug()<<"接受到讯号";
    shownew();
}
announcepage::~announcepage()
{
    delete ui;
}
void announcepage::setlistinfo()
{
    m1=new QStringListModel(ui->listView);
    //建立字符串列表模型对象空间并指定父对象
    //将字符串列表模型设置到树形视图
    ui->listView->setModel(m1);
    //字符串形式输入数据
    QSqlQuery query;
    QString cla=QString("公告信息");
    QString sql=QString("select * from news_table where news_classify='%1'").arg(cla);

    query.exec(sql);
    while(query.next())
    {
        //取出标题
        QString str=query.value("news_title").toString();
        //所添加行的位置
        int row=m1->rowCount();
        //插入行
        m1->insertRow(row);
        QModelIndex index=m1->index(row);
        m1->setData(index,str);
        ui->listView->setCurrentIndex(index);
    }
}
void announcepage::on_toclassBtn_clicked()
{
    mainpage2* w=new mainpage2();
    w->show();
    this->close();
}


void announcepage::on_tostudentBtn_clicked()
{
    studentpage* w=new studentpage();
    w->show();
    this->close();
}


void announcepage::on_toteacherBtn_clicked()
{
    teacherpage* w=new teacherpage();
    w->show();
    this->close();
}

void announcepage::on_deleteBtn_clicked()
{
    QMessageBox::StandardButton box;
    box = QMessageBox::question(this, "提示", "确实要删除这一行的内容吗?", QMessageBox::Yes|QMessageBox::No);
    if(box==QMessageBox::No)return;
    else
    {
        int row=ui->listView->currentIndex().row();
        QModelIndex index1=m1->index(row);
        qDebug()<<row;
        QString deletename=m1->data(index1).toString();
         QSqlQuery query;
         QString sql=QString("delete from news_table where news_title='%1'").arg(deletename);
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

void announcepage::shownew()
{
    m1->removeRows(0,m1->rowCount());
    QSqlQuery query;
    QString cla;
    int index=ui->tabWidget->currentIndex();
    if(index==0)
    {
        cla=QString("公告信息");
    }
    else if(index==1)
    {
        cla=QString("学校文件");
    }else if(index==2)
    {
        cla=QString("党务文件");
    }
    else if(index==3)
    {
        cla=QString("教育教学");
    }else if(index==4)
    {
        cla=QString("学生工作");
    }
    else if(index==5)
    {
        cla=QString("后勤工作");
    }else if(index==6)
    {
        cla=QString("讲座论坛");
    }
    else if(index==7)
    {
        cla=QString("人才招聘");
    }
    else if(index==8)
    {
        cla=QString("科研事项公示");
    }else
    {
        qDebug()<<"没有此项";
    }
    //字符串形式输入数据
    QString sql=QString("select * from news_table where news_classify='%1'").arg(cla);
    query.exec(sql);
    while(query.next())
    {
        //取出标题
        QString str=query.value("news_title").toString();
        //所添加行的位置
        int row=m1->rowCount();
        //插入行
        m1->insertRow(row);
        QModelIndex index=m1->index(row);
        m1->setData(index,str);
        ui->listView->setCurrentIndex(index);
    }
}
void announcepage::on_tabWidget_currentChanged(int index)
{
    shownew();
}


void announcepage::on_publishBtn_clicked()
{
    QString text=ui->textEdit->toPlainText();
    QString where=ui->whereEdit->text();
    QString title=ui->titleEdit->text();
    QDateTime datetime=QDateTime::currentDateTime();
    QString time=datetime.toString("yyyy-MM-dd hh:mm:ss");
    QSqlQuery query;

    if(text=="")
    {
        QMessageBox::warning(NULL,"Warning","内容不能为空");
        return;
    }
    if(where=="")
    {
        QMessageBox::warning(NULL,"Warning","发送部门不能为空");
        return;
    }
    if(title=="")
    {
        QMessageBox::warning(NULL,"Warning","标题不能为空");
        return;
    }
    int index=ui->comboBox->currentIndex();
    QString cla;
    if(index==0)
    {
        cla=QString("公告信息");
    }
    else if(index==1)
    {
        cla=QString("学校文件");
    }else if(index==2)
    {
        cla=QString("党务文件");
    }
    else if(index==3)
    {
        cla=QString("教育教学");
    }else if(index==4)
    {
        cla=QString("学生工作");
    }
    else if(index==5)
    {
        cla=QString("后勤工作");
    }else if(index==6)
    {
        cla=QString("讲座论坛");
    }
    else if(index==7)
    {
        cla=QString("人才招聘");
    }
    else if(index==8)
    {
        cla=QString("科研事项公示");
    }else
    {
        qDebug()<<"没有此项";
        return;
    }
    QSqlQuery test;
    test.exec(QString("select * from dep_table where dep_table.department='%1'").arg(where));
    if(!test.next()){
        QMessageBox::warning(NULL,"警告","不存在该部门请重输");
        return;
    }
    //没有进行输入内容的检验，比如说不能重名，调用announ里面
    QString sqlerror=QString("select * from news_table where news_title='%1").arg(title);
    QSqlQuery querye;
    if(querye.exec(sqlerror))
    {
        QMessageBox::warning(NULL,"警告","该标题已存在，请重新输入");
        return;
    }
    QString sql=QString("insert into news_table(news_classify,news_content,news_time,news_where,news_title)values('%1','%2','%3','%4','%5')").arg(cla).arg(text).arg(time).arg(where).arg(title);
    qDebug()<<"公告sql："<<sql;
    if(query.exec(sql))
    {
        qDebug()<<"创建公告成功";
    }
    else
    {
        QMessageBox::warning(NULL,"Error","执行错误，创建失败！");
        qDebug()<<"创建公告失败";
    }
    ui->tabWidget->setCurrentIndex(index);
    m1->removeRows(0,m1->rowCount());
    QSqlQuery query1;
    QString sql1=QString("select * from news_table where news_classify='%1'").arg(cla);
    query1.exec(sql1);
    while(query1.next())
    {
        //取出标题
        QString str=query1.value("news_title").toString();
        //所添加行的位置
        int row=m1->rowCount();
        //插入行
        m1->insertRow(row);
        QModelIndex index=m1->index(row);
        m1->setData(index,str);
        ui->listView->setCurrentIndex(index);
    }
}


void announcepage::on_searchBtn_clicked()
{
    m1->removeRows(0,m1->rowCount());
    QString search=ui->searchEdit->text();
    QString sql=QString("select * from news_table where news_title like '%"+search+"%' OR news_content like '%"+search+"%'");
    QSqlQuery query;
    if(query.exec(sql))
    {
        qDebug()<<"查询成功";
    }
    //加不加都不行！
    //query.next();
     //QString str=query.value("news_title").toString();
    while(query.next())
    {
        //取出标题
        QString str=query.value("news_title").toString();
        qDebug()<<str;
        //所添加行的位置
        int row=m1->rowCount();
        //插入行
        m1->insertRow(row);
        QModelIndex index=m1->index(row);
        m1->setData(index,str);
        ui->listView->setCurrentIndex(index);
    }
}


void announcepage::on_listView_doubleClicked(const QModelIndex &index)
{
    int row=ui->listView->currentIndex().row();
    QModelIndex index1=m1->index(row);
    QString refreshname=m1->data(index1).toString();
    qDebug()<<refreshname;
    news_ope* newpage=new news_ope();
    newpage->show();
    connect(newpage,&news_ope::closed,this,&announcepage::gets);
    QSqlQuery query;
    QString sql=QString("select * from news_table where news_title='%1'").arg(refreshname);
    if(query.exec(sql))
    {
         qDebug()<<"执行成功";
    }
    else  qDebug()<<"显示失败";
        while(query.next())
    {
        qDebug()<<"success!";
        QString classify=query.value("news_classify").toString();
        qDebug()<<classify;
        if(classify==QString("公告信息"))
        {
                newpage->ui->comboBox->setCurrentIndex(0);
        }
        else if(classify==QString("学校文件"))
        {
               newpage->ui->comboBox->setCurrentIndex(1);
        }else if(QString("党务文件")==classify)
        {
               newpage->ui->comboBox->setCurrentIndex(2);
        }
        else if(classify==QString("教育教学"))
        {
                newpage->ui->comboBox->setCurrentIndex(3);
        }else if(classify==QString("学生工作"))
        {
               newpage->ui->comboBox->setCurrentIndex(4);
        }
        else if(classify==QString("后勤工作"))
        {
                newpage->ui->comboBox->setCurrentIndex(5);
        }else if(classify==QString("讲座论坛"))
        {
               newpage->ui->comboBox->setCurrentIndex(6);
        }
        else if(classify==QString("人才招聘"))
        {
                newpage->ui->comboBox->setCurrentIndex(7);
        }
        else if(classify==QString("科研事项公示"))
        {
                newpage->ui->comboBox->setCurrentIndex(8);
        }else
        {
                qDebug()<<"没有此项";
        }
        QString title=query.value("news_title").toString();
        newpage->ui->titleEdit->setText(title);
        QString text=query.value("news_content").toString();
        newpage->ui->textEdit->setText(text);
        QString where=query.value("news_where").toString();
        newpage->ui->whereEdit->setText(where);
        QString time=query.value("news_time").toString();
        newpage->ui->timeEdit->setText(time);
        newpage->ope_name=title;
    }
}


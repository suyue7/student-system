#include "announcepage_teacher.h"
#include "ui_announcepage_teacher.h"
#include "favoriteswidget_teacher.h"
announcepage_teacher::announcepage_teacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::announcepage_teacher)
{
    ui->setupUi(this);

    ui->namelabel->setText("姓名：" + MainWindow::sfName);
    ui->uidlabel->setText("ID：" + MainWindow::sfID);
    //设置表格,现在测试的是课程表格
    this->setlistinfo();
    //设置默认表格为新增页面
    ui->tabWidget->setCurrentIndex(0);
    ui->searchEdit->setPlaceholderText("请输入关键词");
}

void announcepage_teacher::gets()
{
    qDebug()<<"接受到讯号";
    shownew();
}

announcepage_teacher::~announcepage_teacher()
{
    delete ui;
}

void announcepage_teacher::setlistinfo()
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

void announcepage_teacher::shownew()
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

void announcepage_teacher::on_tabWidget_currentChanged(int index)
{
    shownew();
}

void announcepage_teacher::on_searchBtn_clicked()
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


void announcepage_teacher::on_listView_doubleClicked(const QModelIndex &index)
{
    int row=ui->listView->currentIndex().row();
    QModelIndex index1=m1->index(row);
    QString refreshname=m1->data(index1).toString();
    qDebug()<<refreshname;
    news_ope_teacher* newpage=new news_ope_teacher();
    newpage->show();
    //connect(newpage,&news_ope::closed,this,&announcepage::gets);
    QSqlQuery query;
    QString sql=QString("select * from news_table where news_title='%1'").arg(refreshname);
    if(query.exec(sql))
         qDebug()<<"执行成功";
    else
        qDebug()<<"显示失败";
    while(query.next())
    {
        //qDebug()<<"success!";
        QString title=query.value("news_title").toString();
        newpage->ui->titlelabel->setText(title);
        QString text=query.value("news_content").toString();
        newpage->ui->textBrowser->setText(text);
        QString where=query.value("news_where").toString();
        newpage->ui->deplabel->setText(where);
        newpage->ui->deplabel->adjustSize();
        QString time=query.value("news_time").toString();
        newpage->ui->timelabel->setText(time);
        newpage->ui->timelabel->adjustSize();
        newpage->ope_name=title;
    }
}


void announcepage_teacher::on_exitBtn_clicked()
{
    close();
}



void announcepage_teacher::on_FavoritesBtn_clicked()
{
    FavoritesWidget_teacher *fw = new FavoritesWidget_teacher();
    fw->show();
}


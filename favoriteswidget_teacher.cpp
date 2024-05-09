#include "favoriteswidget_teacher.h"
#include "ui_favoriteswidget_teacher.h"
#include "mainwindow.h"
#include<QSqlQuery>
FavoritesWidget_teacher::FavoritesWidget_teacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FavoritesWidget_teacher)
{
    ui->setupUi(this);

    QSqlQuery query;
    QString sql = QString("select * from news_table a inner join like_table b on a.news_id = b.news_id");
    query.exec(sql);
    while(query.next()){
        newsinfo.append(new news(query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),query.value(4).toString(),query.value(5).toString()));
        title.append(query.value("news_title").toString());
    }

    QCompleter *m_pCompleter = new QCompleter(title);
    m_pCompleter->setFilterMode(Qt::MatchContains);
    ui->searchEdit->setCompleter(m_pCompleter);
    ui->searchEdit->setPlaceholderText("请输入关键词");

    //设置表格,现在测试的是课程表格
    this->setlistinfo();
    //设置默认表格为新增页面
    ui->tabWidget->setCurrentIndex(0);
}

FavoritesWidget_teacher::~FavoritesWidget_teacher()
{
    delete ui;
}

void FavoritesWidget_teacher::gets()
{
    qDebug()<<"接受到讯号";
    shownew();
}

void FavoritesWidget_teacher::setlistinfo()
{
    m1=new QStringListModel(ui->listView);
    //建立字符串列表模型对象空间并指定父对象
    //将字符串列表模型设置到树形视图
    ui->listView->setModel(m1);
    //字符串形式输入数据
    QSqlQuery query;
    QString cla = QString("公告信息");

    for(int i = 0; i < newsinfo.size(); i++){
        if(newsinfo[i]->classify==cla){
            //所添加行的位置
            int row = m1->rowCount();
            //插入行
            m1->insertRow(row);
            QModelIndex index=m1->index(row);
            m1->setData(index,newsinfo[i]->title);
            ui->listView->setCurrentIndex(index);
        }
    }
}

void FavoritesWidget_teacher::shownew()
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
    for(int i = 0; i < newsinfo.size(); i++){
        if(newsinfo[i]->classify==cla){
            //所添加行的位置
            int row = m1->rowCount();
            //插入行
            m1->insertRow(row);
            QModelIndex index=m1->index(row);
            m1->setData(index,newsinfo[i]->title);
            ui->listView->setCurrentIndex(index);
        }
    }
}

void FavoritesWidget_teacher::on_tabWidget_currentChanged(int index)
{
    shownew();
}

void FavoritesWidget_teacher::on_searchBtn_clicked()
{
    m1->removeRows(0,m1->rowCount());
    QString search=ui->searchEdit->text();
    for(int i = 0; i < title.size(); i++){
        if(title[i].indexOf(search)!=-1){
            //所添加行的位置
            int row=m1->rowCount();
            //插入行
            m1->insertRow(row);
            QModelIndex index=m1->index(row);
            m1->setData(index,title[i]);
            ui->listView->setCurrentIndex(index);
        }
    }
}

void FavoritesWidget_teacher::on_listView_doubleClicked(const QModelIndex &index)
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

void FavoritesWidget_teacher::on_exitButton_clicked()
{
    for(int i = 0; i < droplist.size(); i++){
        int k = title.indexOf(droplist[i]);
        if(k!=-1){
            title.removeAt(k);
            for(int j = 0; j < newsinfo.size(); j++){
                if(newsinfo[j]->title == droplist[i]){
                    QString sql = QString("DELETE FROM like_table WHERE news_id = '%1' AND per_id = '%2'").arg(newsinfo[j]->id, MainWindow::sfID);
                    qDebug() << sql;
                    QSqlQuery q;
                    q.exec(sql);
                    delete newsinfo[j];
                    newsinfo[j] = nullptr;
                    newsinfo.removeAt(j);
                    break;
                }
            }
        }
    }
    close();
}


void FavoritesWidget_teacher::on_dropButton_clicked()
{
    //获得选择的序列号
    QItemSelectionModel *selmodel = ui->listView->selectionModel();
    if (selmodel)
    {
        QModelIndexList indexlist = selmodel->selectedIndexes();
        int count1 = indexlist.size();
        for(int i = 0; i < count1; i++){
            QString str = ui->listView->model()->data(indexlist[i]).toString();
            int id = droplist.indexOf(str);
            if(id==-1){
                droplist.append(str);
                ui->dropButton->setText("恢复收藏");
            }else{
                droplist.removeAt(id);
                ui->dropButton->setText("取消收藏");
            }
        }
    }
}


void FavoritesWidget_teacher::on_listView_clicked(const QModelIndex &index)
{
    //获得选择的序列号
    QItemSelectionModel *selmodel = ui->listView->selectionModel();
    if (selmodel)
    {
        QModelIndexList indexlist = selmodel->selectedIndexes();
        int count1 = indexlist.size();
        for(int i = 0; i < count1; i++){
            QString str = ui->listView->model()->data(indexlist[i]).toString();
            int id = droplist.indexOf(str);
            if(id!=-1)
                ui->dropButton->setText("恢复收藏");
            else
                ui->dropButton->setText("取消收藏");
        }
    }
}


#include "news_ope.h"
#include "ui_news_ope.h"
news_ope::news_ope(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::news_ope)
{
    ui->setupUi(this);
    QString sql=QString("select * from dep_table");
    QSqlQuery query;
    query.exec(sql);
    while(query.next())
    {
        listData<<query.value("department").toString();
    }
    QCompleter *m_pCompleter = new QCompleter(listData);
    m_pCompleter->setFilterMode(Qt::MatchContains);
    ui->whereEdit->setCompleter(m_pCompleter);
}

news_ope::~news_ope()
{
    delete ui;
}

void news_ope::on_refreshBtn_clicked()
{
    QString text=this->ui->textEdit->toPlainText();
    QString where=this->ui->whereEdit->text();
    QString title=this->ui->titleEdit->text();
    QString time=this->ui->timeEdit->text();
    QDateTime datetime=QDateTime::currentDateTime();
    QString curtime=datetime.toString("yyyy-MM-dd hh:mm:ss");
    qDebug()<<curtime;
    QSqlQuery query;

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
    }
    if(title==""){
        QMessageBox::warning(this, "警告", "标题内容不能为空！");
        return;
    }
    if(text==""){
        QMessageBox::warning(this, "警告", "文本内容不能为空！");
        return;
    }
    if(where==""){
        QMessageBox::warning(this, "警告", "发布方单位不能为空！");
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
    QString sql=QString("update news_table set news_classify='%1',news_content='%2',news_time='%3',news_where='%4',news_title='%5' where news_title='%6'").arg(cla).arg(text).arg(curtime).arg(where).arg(title).arg(ope_name);
    if(query.exec(sql))
    {
        qDebug()<<"修改公告成功";

    }
    else
    {
         QMessageBox::warning(NULL,"警告","执行错误，创建失败！");
        qDebug()<<"修改公告失败";
    }
    ope_name=title;
    emit closed();
    this->close();
}

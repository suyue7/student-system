#include "studentwidget.h"
#include "ui_studentwidget.h"
#include "mainwindow.h"
#include "scorepic.h"
#include "scorefinish.h"
#include "announcepage_teacher.h"
#include "helpwidget.h"
#include "classtable.h"
#include "logindialog.h"
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QTableWidget>
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QFile>
#include <QFileDialog>
#include <QModelIndex>
#include <regex>

StudentWidget::StudentWidget(QWidget *parent,QString user1):
    QWidget(parent),
    ui(new Ui::StudentWidget)
{
    ui->setupUi(this);
    qDebug()<<"学生登录成功！";
    user=user1;
    qDebug()<<"当前用户:"<<user;
    this->setWindowTitle("学生首页");

    //个人资料
    ui->label_10->lower();
    ui->editInfo->setIcon(QIcon("image/right.png"));
    ui->editInfo->setLayoutDirection(Qt::RightToLeft);
    ui->checkFinish->setIcon(QIcon("image/chart.png"));
    ui->checkFinish->setLayoutDirection(Qt::LeftToRight);
    ui->checkPic->setIcon(QIcon("image/pie.png"));
    ui->checkPic->setLayoutDirection(Qt::LeftToRight);
    ui->assessSub->setIcon(QIcon("image/right.png"));
    ui->assessSub->setLayoutDirection(Qt::RightToLeft);
    ui->checkClass->setIcon(QIcon("image/course.jpg"));
    ui->checkClass->setLayoutDirection(Qt::RightToLeft);
    ui->exportScore->setIcon(QIcon("image/file.png"));
    ui->exportScore->setLayoutDirection(Qt::LeftToRight);    //加入按钮图片

    QPixmap qp1("image/person.png");
    ui->picLabel->setPixmap(qp1);
    ui->picLabel->setScaledContents(true);
    ui->picLabel->show();

    QPixmap qp2("image/edit.png");
    ui->edit->setPixmap(qp2);
    ui->edit->setScaledContents(true);
    ui->edit->show();

    QPixmap qp3("image/rank.png");
    ui->rank->setPixmap(qp3);
    ui->rank->setScaledContents(true);
    ui->rank->show();

    QPixmap qp4("image/Warn.png");
    ui->warn->setPixmap(qp4);
    ui->warn->setScaledContents(true);
    ui->warn->show();

    QIcon iconNews("image/news.png");
    QPixmap qp=iconNews.pixmap(QSize(35,35));
    ui->newsBtn->setIcon(QIcon(qp));
    ui->newsBtn->setIconSize(QSize(35,35));
    ui->newsBtn->setToolTip("校园公告");

    QIcon iconNews1("image/helpWg.png");
    qp=iconNews1.pixmap(QSize(35,35));
    ui->helpBtn->setIcon(QIcon(qp));
    ui->helpBtn->setIconSize(QSize(35,35));
    ui->helpBtn->setToolTip("帮助文档");

    ui->selectLesson->setIcon(QIcon("image/right.png"));
    ui->selectLesson->setLayoutDirection(Qt::RightToLeft);
    ui->cancelLesson->setIcon(QIcon("image/wrong.png"));
    ui->cancelLesson->setLayoutDirection(Qt::RightToLeft);

    QSqlQuery queryn;
    QString sqln=QString("select * from student_table where sid='%1'").arg(user);
    queryn.exec(sqln);
    queryn.next();
    ui->nameLabel->setText("id："+user);
    ui->nameLabel->setFixedWidth(160);
    ui->nameLabel_2->setText("姓名："+queryn.value(2).toString());
    ui->nameLabel_2->setFixedWidth(160);
    queryn.clear();
    QSqlQuery queryl;
    QString sqll=QString("select * from selectedlesson where sid='%1'").arg(user); //选出该用户
    qDebug()<<sqll;
    if(queryl.exec(sqll))
    {
        qDebug()<<"查询已选课程数成功！";       //查询当前用户所选课程数
        while (queryl.next())
            lessonNum++;
    }
    qDebug()<<"当前选课数："<<lessonNum;
    selNum=lessonNum;

    //设置个人资料展示表格
    ui->infoWidget->setShowGrid(true);
    ui->infoWidget->setRowCount(8);
    ui->infoWidget->setColumnCount(1);
    ui->infoWidget->horizontalHeader()->hide();
    ui->infoWidget->setVerticalHeaderLabels(QStringList()<<"id"<<"密码"<<"姓名"<<"性别"<<"学院"<<"手机号"<<"家庭住址"<<"年级");
    ui->infoWidget->setLineWidth(15);
    ui->infoWidget->setColumnWidth(0,150);
    ui->infoWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->infoWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->infoWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->infoWidget->setSelectionMode(QAbstractItemView::NoSelection);

    QSqlQuery query;
    QString sql=QString("select * from student_table where sid='%1'").arg(user);
    if (query.exec(sql)&&query.first())
        for (int i=0;i<8;i++)
        {
            ui->infoWidget->setItem(i,0,new QTableWidgetItem(query.value(i).toString()));
            ui->infoWidget->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }

    //个人资料修改框
    ui->lineEdit->setText(query.value(0).toString());
    ui->lineEdit_2->setText(query.value(1).toString());
    ui->lineEdit_3->setText(query.value(2).toString());
    ui->lineEdit_4->setText(query.value(3).toString());
    ui->lineEdit_5->setText(query.value(4).toString());
    ui->lineEdit_6->setText(query.value(5).toString());
    ui->lineEdit_8->setText(query.value(6).toString());
    ui->lineEdit_7->setText(query.value(7).toString());

    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_5->setReadOnly(true);
    ui->lineEdit_7->setReadOnly(true);

    //选退课，lessonList为可选课程，myLesson为已选课程，表头相同
    query.clear();
    query.exec(" SELECT * FROM class_table");
    int sum1=0;
    while (query.next())
        if (query.value("is_apply").toInt()==1) sum1++;
    ui->lessonList->setShowGrid(true);
    ui->lessonList->setColumnCount(10);
    ui->lessonList->setRowCount(sum1);
    ui->lessonList->setHorizontalHeaderLabels(QStringList()<<"课程id"<<"名称"<<"性质"<<"学分"<<"开设学院"<<"授课老师"<<"地点"<<"时间"<<"容量"<<"考核方式");
    ui->lessonList->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(235,244,254);;}");
    ui->lessonList->horizontalHeader()->setHighlightSections(false);

    ui->myLesson->setShowGrid(true);
    ui->myLesson->setColumnCount(10);
    ui->myLesson->setHorizontalHeaderLabels(QStringList()<<"课程id"<<"名称"<<"性质"<<"学分"<<"开设学院"<<"授课老师"<<"地点"<<"时间"<<"容量"<<"考核方式");
    ui->myLesson->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(235,244,254);;}");
    ui->myLesson->horizontalHeader()->setHighlightSections(false);
    ui->myLesson->setColumnWidth(0,50);
    ui->myLesson->setColumnWidth(1,110);
    ui->myLesson->setColumnWidth(2,70);
    ui->myLesson->setColumnWidth(3,40);
    ui->myLesson->setColumnWidth(4,100);
    ui->myLesson->setColumnWidth(5,70);
    ui->myLesson->setColumnWidth(6,80);
    ui->myLesson->setColumnWidth(7,125);
    ui->myLesson->setColumnWidth(8,40);
    ui->myLesson->setColumnWidth(9,60);
    ui->myLesson->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->myLesson->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->myLesson->setSelectionBehavior(QAbstractItemView::SelectRows);

    query.clear();
    QString sqlc=QString("select * from selectedlesson where sid='%1'").arg(user);
    query.exec(sqlc);
    query.first();
    QSqlQuery querya;
    QString sqla;
    for (int i=0;i<lessonNum;i++)     //显示已选课程
    {
        ui->myLesson->insertRow(i);
        ui->myLesson->setItem(i,0,new QTableWidgetItem(query.value(1).toString()));
        sqla=QString("SELECT * FROM class_table WHERE cid='%1'").arg(query.value(1).toString());
        querya.exec(sqla);
        querya.first();
        QSqlQuery tmpsql;
        QString tmpstr;
        for (int j=1;j<9;j++)
        {
            if (j!=5)
                ui->myLesson->setItem(i,j,new QTableWidgetItem(querya.value(j).toString()));
            if (j==7)  //时间
            {
                tmpsql.clear();
                sqla=QString("SELECT * FROM arr_table WHERE cid='%1'").arg(query.value(1).toString());  //课程id
                tmpsql.exec(sqla);
                tmpstr.clear();
                while (tmpsql.next())
                {
                    int hh=tmpsql.value("weekday").toInt();
                    if (hh==1) tmpstr.append("周一");
                    if (hh==2) tmpstr.append("周二");
                    if (hh==3) tmpstr.append("周三");
                    if (hh==4) tmpstr.append("周四");
                    if (hh==5) tmpstr.append("周五");
                    if (hh==6) tmpstr.append("周六");
                    if (hh==7) tmpstr.append("周日");
                    tmpstr.append("第");
                    QString dd=tmpsql.value("classtime").toString();
                    tmpstr.append(dd);
                    tmpstr.append("节;");
                }
                ui->myLesson->setItem(i,j,new QTableWidgetItem(tmpstr));
            }
        }

        ui->myLesson->setItem(i,9,new QTableWidgetItem(querya.value(11).toString()));
        sqla=QString("SELECT * FROM teacher_table WHERE tid='%1'").arg(querya.value("tid").toString());
        querya.clear();
        querya.exec(sqla);
        querya.first();
        ui->myLesson->setItem(i,5,new QTableWidgetItem(querya.value("tname").toString()));
        querya.clear();
        query.next();
    }

    QSqlQuery query1,tmpsql;
    QString tmpstr;
    query1.exec(" SELECT * FROM class_table");
    int j=0;
    while (query1.next())
    {
        //qDebug()<<query1.value("cid").toString()<<":"<<query1.value("is_apply").toInt()<<":";
        if (query1.value("is_apply").toInt()==0) continue;
        for (int i=0;i<9;i++)
        {
            if (i!=5)
                ui->lessonList->setItem(j,i,new QTableWidgetItem(query1.value(i).toString()));
            if (i==7)  //时间
            {
                tmpsql.clear();
                sqla=QString("SELECT * FROM arr_table WHERE cid='%1'").arg(query1.value(0).toString());  //课程id
                tmpsql.exec(sqla);
                tmpstr.clear();
                while (tmpsql.next())
                {
                    int hh=tmpsql.value("weekday").toInt();
                    if (hh==1) tmpstr.append("周一");
                    if (hh==2) tmpstr.append("周二");
                    if (hh==3) tmpstr.append("周三");
                    if (hh==4) tmpstr.append("周四");
                    if (hh==5) tmpstr.append("周五");
                    if (hh==6) tmpstr.append("周六");
                    if (hh==7) tmpstr.append("周日");
                    tmpstr.append("第");
                    QString dd=tmpsql.value("classtime").toString();
                    tmpstr.append(dd);
                    tmpstr.append("节;");
                }
                ui->lessonList->setItem(j,i,new QTableWidgetItem(tmpstr));
            }
        }
        ui->lessonList->setItem(j,9,new QTableWidgetItem(query1.value(11).toString()));
        sqla=QString("SELECT * FROM teacher_table WHERE tid='%1'").arg(query1.value("tid").toString());
        querya.clear();
        querya.exec(sqla);
        querya.first();
        ui->lessonList->setItem(j,5,new QTableWidgetItem(querya.value("tname").toString()));
        j++;
    }

    ui->myLesson->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lessonList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lessonList->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->lessonList->setColumnWidth(0,50);
    ui->lessonList->setColumnWidth(1,110);
    ui->lessonList->setColumnWidth(2,70);
    ui->lessonList->setColumnWidth(3,40);
    ui->lessonList->setColumnWidth(4,100);
    ui->lessonList->setColumnWidth(5,70);
    ui->lessonList->setColumnWidth(6,80);
    ui->lessonList->setColumnWidth(7,125);
    ui->lessonList->setColumnWidth(8,40);
    ui->lessonList->setColumnWidth(9,60);

    ui->lessonList->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->lessonList->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    //成绩查询
    ui->scoreReview->verticalHeader()->hide();
    QSqlQueryModel *model=new QSqlQueryModel();
    QString sql3=QString("SELECT score_table.cid,sscore,cname FROM score_table,class_table WHERE sid='%1' and score_table.cid=class_table.cid;").arg(user);
    model->setQuery(sql3);
    qDebug()<<sql3;
    ui->scoreReview->setModel(model);

    model->setHeaderData(0,Qt::Horizontal,"课程id");
    model->setHeaderData(1,Qt::Horizontal,"分数");
    model->setHeaderData(2,Qt::Horizontal,"课程名称");
    ui->scoreReview->show();
    ui->scoreReview->setSelectionMode(QAbstractItemView::NoSelection);

    double userScore;
    QSqlQuery queryb;
    query.exec("SELECT * FROM student_table");
    while (query.next())
    {
        QString thisUser=query.value("sid").toString();
        sql3=QString("SELECT * FROM score_table WHERE sid='%1'").arg(thisUser);
        querya.clear();
        querya.exec(sql3);
        int scoSum=0,xfSum=0;
        while (querya.next())
        {
            int lesSco=querya.value("sscore").toInt();
            queryb.clear();
            QString tmp=QString("SELECT * FROM class_table WHERE cid='%1'").arg(querya.value("cid").toString());
            queryb.exec(tmp);
            queryb.first();
            int xf=queryb.value("cscore").toInt();
            if (lesSco>=60)
                scoSum+=(lesSco-50)*0.1*xf;             //scoSum：绩点之和，xfSum：学分之和
            xfSum+=xf;
        }
        double thisScore=scoSum*1.0/xfSum;
        if (query.value("sid")==user) userScore=thisScore;
        sql3=QString("UPDATE student_table SET gpa=%1 WHERE sid='%2'").arg(thisScore).arg(thisUser);
        queryb.clear();
        queryb.exec(sql3);
    }

    int grade=0;
    int sum=1;
    query.clear();
    query.exec("SELECT * FROM student_table");
    while (query.next())
    {
        sum++;
        if (query.value("sid").toString()!=user)
            if (query.value("gpa").toDouble()>userScore) grade++;
    }
    ui->scoreTable->setRowCount(2);
    ui->scoreTable->setColumnCount(2);
    ui->scoreTable->setColumnWidth(0,100);
    ui->scoreTable->setColumnWidth(1,180);
    ui->scoreTable->setRowHeight(0,40);
    ui->scoreTable->setRowHeight(1,40);
    ui->scoreTable->setItem(0,0,new QTableWidgetItem("平均绩点"));
    ui->scoreTable->setItem(1,0,new QTableWidgetItem("平均排名"));
    ui->scoreTable->setItem(0,1,new QTableWidgetItem(QString::number(userScore,'f',2)));
    QString showGrade=QString("%1 %2 %3").arg(QString::number(grade)).arg("/").arg(QString::number(sum));

    ui->scoreTable->setItem(1,1,new QTableWidgetItem(showGrade));
    ui->scoreTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->scoreTable->verticalHeader()->hide();
    ui->scoreTable->horizontalHeader()->hide();
    ui->scoreTable->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->scoreTable->item(1,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->scoreTable->item(0,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->scoreTable->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->scoreTable->setSelectionMode(QAbstractItemView::NoSelection);

    //学业预警表格，低于60分显示
    query.clear();
    QString wa=QString("SELECT * FROM score_table WHERE sid='%1'").arg(user);
    query.exec(wa);
    int warningNum=0;
    ui->scoreWarning->setColumnCount(2);
    ui->scoreWarning->setHorizontalHeaderLabels(QStringList()<<"课程名称"<<"成绩");
    ui->scoreWarning->setColumnWidth(1,100);
    ui->scoreWarning->setColumnWidth(1,180);
    ui->scoreWarning->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->scoreWarning->verticalHeader()->hide();
    ui->scoreWarning->setSelectionMode(QAbstractItemView::NoSelection);
    QSqlQuery queryw;
    while (query.next())
    {
        int scoWa=query.value("sscore").toInt();
        if (scoWa<60)
        {
            queryw.clear();
            QString sqlw=QString("SELECT * FROM class_table WHERE cid='%1'").arg(query.value("cid").toString());
            qDebug()<<sqlw;
            queryw.exec(sqlw);
            queryw.first();
            ui->scoreWarning->insertRow(warningNum);
            ui->scoreWarning->setItem(warningNum,0,new QTableWidgetItem(queryw.value("cname").toString()));
            ui->scoreWarning->setItem(warningNum,1,new QTableWidgetItem(QString::number(scoWa)));
            ui->scoreWarning->item(warningNum,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->scoreWarning->item(warningNum,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            warningNum++;
        }
    }
    this->model=model;

    //评教
    ui->assessSub->setIcon(QIcon ("image/ok.png"));
    ui->assessSub->setLayoutDirection(Qt::RightToLeft);
    query.clear();
    query1.clear();
    QString sl=QString("SELECT * FROM selectedlesson WHERE sid='%1'").arg(user);
    query.exec(sl);

    query1.clear();
    while (query.next())
    {
        QString ln=QString("SELECT * FROM class_table WHERE cid='%1'").arg(query.value(1).toString());
        query1.exec(ln);
        if (query1.first())
            ui->assessbox->addItem(query1.value(1).toString());
        query1.clear();
    }

}

StudentWidget::~StudentWidget()
{
    delete ui;
}

void StudentWidget::on_selectLesson_clicked()  //选课
{
    QList<QTableWidgetItem*> items=ui->lessonList->selectedItems();
    if (!items.empty())
    {
        QSqlQuery query3;
        QString sql3=QString("select * from selectedlesson where sid='%1'").arg(user); //选出该用户
        query3.exec(sql3);
        bool ifchosen=false;
        while (query3.next())
        {
            if (query3.value(1).toString()==items.at(0)->text())   //出现过课程id即为选过
            {
                QMessageBox::information(this,"警告","不可重复选择课程！");
                ifchosen=true;
                break;
            }
        }
        if (!ifchosen)  //未选
        {
            query3.first();
            //判断课程时间是否冲突
            QSqlQuery ctquery;
            QString ctsql;

            QString classId=items.at(0)->text();  //课程id

            ctsql=QString("SELECT * FROM arr_table WHERE cid='%1'").arg(classId);
            qDebug()<<"ctsql1:"<<ctsql;
            ctquery.exec(ctsql);
            ctquery.first();
            QString thisWeek=ctquery.value("weekday").toString();
            QString thisTime=ctquery.value("classtime").toString();

            ctsql=QString("SELECT * FROM arr_table WHERE cid='%1'").arg(query3.value("cid").toString());
            qDebug()<<"ctsql2:"<<ctsql;
            ctquery.clear();
            ctquery.exec(ctsql);
            while (ctquery.next())
            {
                if (ctquery.value("weekday").toString()==thisWeek&&ctquery.value("classtime").toString()==thisTime)
                {
                    QMessageBox::information(this,"温馨提示","课程时间冲突！");
                    return;
                }
            }

            while (query3.next())
            {
                ctsql=QString("SELECT * FROM arr_table WHERE cid='%1'").arg(query3.value(1).toString());
                ctquery.clear();
                ctquery.exec(ctsql);
                while (ctquery.next())
                {
                    if (ctquery.value("weekday").toString()==thisWeek&&ctquery.value("classtime").toString()==thisTime)
                    {
                        QMessageBox::information(this,"温馨提示","课程时间冲突！");
                        return;
                    }
                }
            }

            ctsql=QString("SELECT * FROM class_table WHERE cid='%1'").arg(items.at(0)->text());
            ctquery.clear();
            ctquery.exec(ctsql);
            ctquery.first();
            if (ctquery.value("ccur").toInt()>=ctquery.value("ccapacity").toInt())
            {QMessageBox::information(this,"温馨提示","当前课程人数已满！");return;}

            lessonNum++;
            selNum++;
            QSqlQuery query4;
            QString sql4=QString("insert into selectedlesson(cid,sid,is_assessed) values('%1','%2',0)").arg(items.at(0)->text()).arg(user);
            qDebug()<<"调试部分sql："<<sql4;
            query4.exec(sql4);
            QMessageBox::information(this,"温馨提示","选课成功！");
            ui->myLesson->insertRow(lessonNum-1);
            for (int i=0;i<10;i++)
                ui->myLesson->setItem(lessonNum-1,i,new QTableWidgetItem(items.at(i)->text()));

            query4.clear();
            QString udsql=QString("UPDATE class_table SET ccur=ccur+1 WHERE cid='%1'").arg(items.at(0)->text());
            query4.exec(udsql);

            ui->assessbox->addItem(items.at(1)->text());
        }
    }
    else QMessageBox::warning(NULL,"警告","请选择课程！");
}

void StudentWidget::on_cancelLesson_clicked()  //退课
{
    QList<QTableWidgetItem*> items=ui->myLesson->selectedItems();
    if (!items.empty())
    {
        QSqlQuery query;
        QString sql;
        sql=QString("SELECT * FROM score_table WHERE sid='%1' AND cid='%2'").arg(user).arg(items.at(0)->text());
        query.exec(sql);
        if (query.first()) {QMessageBox::warning(NULL,"警告","该门课程已过退课时间！");return;}

        query.clear();
        sql=QString("SELECT * FROM selectedlesson WHERE sid='%1' AND cid='%2' AND is_assessed=1").arg(user).arg(items.at(0)->text());
        query.exec(sql);
        if (query.first()) {QMessageBox::warning(NULL,"警告","该门课程已过退课时间！");return;}

        lessonNum--;

//        query.first();
//        sql=QString("DELETE FROM selectedlesson WHERE cid='%1' AND sid='%2'").arg(items.at(0)->text()).arg(user);

//        query.clear();
//        query.exec(sql);
        query.clear();
        sql=QString("SELECT * FROM selectedlesson WHERE cid='%1' AND sid='%2'").arg(items.at(0)->text()).arg(user);
        query.exec(sql);
        int qs=0;
        while (query.next())
            qs++;
        qDebug()<<"qs="<<qs;
        query.first();
        sql=QString("DELETE FROM selectedlesson WHERE sel_id='%1'").arg(query.value("sel_id").toString());

        query.clear();
        query.exec(sql);
        qDebug()<<sql;

        QMessageBox::information(this,"温馨提示","退课成功！");
        int rowIndex=ui->myLesson->currentRow();
        if (rowIndex!=-1)
            ui->myLesson->removeRow(rowIndex);
        query.clear();
//        qDebug()<<"ITEMS:"<<items.at(0)->text();

//        sql=QString("SELECT * FROM class_table WHERE cid='%1'").arg(items.at(0)->text());
//        query.exec(sql);
//        int curr=query.value("ccur").toInt();
//        curr++;
//        sql=QString("UPDATE class_table SET ccur=ccur+1 WHERE cid='%1'").arg(items.at(0)->text());
//        qDebug()<<"UPDATE:"<<sql;
//        query.exec(sql);

//        qDebug()<<"课程名："<<items.at(1)->text();
//        int ii=ui->assessbox->findText(items.at(1)->text());
//        qDebug()<<"ii:"<<ii;
//        ui->assessbox->removeItem(ii);
    }
    else QMessageBox::warning(NULL,"警告","请选择课程！");
}

void StudentWidget::on_editInfo_clicked()   //修改个人资料
{
    QString pw=ui->lineEdit_2->text();
    QString pn=ui->lineEdit_6->text();
    QString ad=ui->lineEdit_8->text();

    //输入非法判断
    if (pw.length()<6) {QMessageBox::warning(this,"警告","密码长度不得少于6位！");return;}
    if (pw.length()>15) {QMessageBox::warning(this,"警告","密码长度不得多于15位！");return;}
    for (int i=0;i<pw.length();i++)
    {
        if (pw[i]>='0'&&pw[i]<='9') continue;
        if (pw[i]>='a'&&pw[i]<='z') continue;
        if (pw[i]>='A'&&pw[i]<='Z') continue;
        QMessageBox::warning(this,"警告","密码只能含有数字和字母！");
        return;
    }
    if (pn.length()!=11) {QMessageBox::warning(this,"警告","请输入合法手机号！");return;}
    std::regex r("^1(3|5|8)\\d{9}$");
    std::string userIdString=pn.toStdString();
    bool bValid=std::regex_match(userIdString,r);
    if(!bValid) {
        QMessageBox::warning(NULL,"警告","请输入合法手机号！");
        return;
    }
    std::regex reg("^[\u4e00-\u9fa5]+省[\u4e00-\u9fa5]+市");
    std::string add=ad.toStdString();
    bValid=std::regex_match(add,reg);
    if (!bValid){
        QMessageBox::warning(NULL,"警告","请输入合法住址！");
        return;
    }

    QSqlQuery query1;
    QString sql1=QString("select * from student_table where sid='%1'").arg(user);
    query1.exec(sql1);
    if (query1.first())
    {
        QTableWidgetItem* item1=ui->infoWidget->item(1,0);
        QTableWidgetItem* item2=ui->infoWidget->item(5,0);
        QTableWidgetItem* item3=ui->infoWidget->item(6,0);
        item1->setText(pw);
        item2->setText(pn);
        item3->setText(ad);
        ui->infoWidget->item(1,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->infoWidget->item(2,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->infoWidget->item(3,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        QSqlQuery query2;
        QString sql2=QString("UPDATE student_table SET spasswd='%1',sphonenumber='%2',saddress='%3' WHERE sid='%4'").arg(pw).arg(pn).arg(ad).arg(user);
        query2.exec(sql2);
    }
    QMessageBox::information(this,"温馨提示","修改成功！");
}

void StudentWidget::on_checkBtn_clicked()   //查询课程id
{
    QString le=ui->checkLesson->text();
    QString sql;
    if (le=="") sql=QString("SELECT score_table.cid,sscore,cname FROM score_table,class_table WHERE sid='%1' and score_table.cid=class_table.cid;").arg(user);
    else sql=QString("SELECT score_table.cid,sscore,cname FROM score_table,class_table WHERE sid='%1' AND score_table.cid='%2' AND score_table.cid=class_table.cid;").arg(user).arg(le);
    QSqlQueryModel *model=new QSqlQueryModel();
    ui->scoreReview->setModel(model);

    model->setQuery(sql);
    ui->scoreReview->setModel(model);
    model->setHeaderData(0,Qt::Horizontal,"课程id");
    model->setHeaderData(1,Qt::Horizontal,"分数");
    model->setHeaderData(2,Qt::Horizontal,"课程名称");
    ui->scoreReview->show();
}

//void StudentWidget::on_checkLesson_2_clicked()   //查询评教课程
void StudentWidget::on_assessbox_activated(int index)
{
    QSqlQuery query;
    QString curLesson=ui->assessbox->currentText();
    if (curLesson=="")
    {
        QMessageBox::information(this,"温馨提示","请选择评教课程！");
        ui->teacherpic->clear();
        ui->score_1->clear();
        ui->score_2->clear();
        ui->score_3->clear();
        ui->score_4->clear();
        ui->commentEdit->clear();
        ui->tcName->clear();
        ui->tcLesson->clear();
        return;
    }

    QString tc=QString("SELECT * FROM class_table WHERE cname='%1'").arg(curLesson);
    query.exec(tc);
    qDebug()<<"tc1："<<tc;
    query.first();

    QString recId=query.value("cid").toString();
    qDebug()<<"Id："<<recId;
    query.clear();
    tc=QString("SELECT * FROM selectedlesson WHERE cid='%1'").arg(recId);
    query.exec(tc);
    qDebug()<<"tc2："<<tc;
    if (!query.first())  //被退掉了
    {
        QMessageBox::information(this,"温馨提示","你未选该门课程！");
        ui->teacherpic->clear();
        ui->score_1->clear();
        ui->score_2->clear();
        ui->score_3->clear();
        ui->score_4->clear();
        ui->commentEdit->clear();
        ui->tcName->clear();
        ui->tcLesson->clear();
        return;
    }

    query.clear();
    tc=QString("SELECT * FROM class_table WHERE cname='%1'").arg(curLesson);
    query.exec(tc);
    query.first();
    if (query.value("is_open").toString()=="0")  //未开放评教
    {
        QMessageBox::information(this,"温馨提示","该课程评教尚未开始！");
        ui->teacherpic->clear();
        ui->score_1->clear();
        ui->score_2->clear();
        ui->score_3->clear();
        ui->score_4->clear();
        ui->commentEdit->clear();
        ui->tcName->clear();
        ui->tcLesson->clear();
        return;
    }

    query.clear();
    tc=QString("SELECT * FROM class_table WHERE cname='%1'").arg(curLesson);
    query.exec(tc);
    if (query.first()) qDebug()<<"查询教师信息成功！";
    QString tc1=QString("SELECT * FROM teacher_table WHERE tid='%1'").arg(query.value("tid").toString());
    QSqlQuery query1;
    query1.exec(tc1);
    query1.first();
    ui->tcName->setText("教师："+query1.value("tname").toString());
    ui->tcLesson->setText("课程："+curLesson);
    QString curId=query.value("cid").toString();

    query.clear();
    tc=QString("SELECT * FROM teacher_table WHERE tname='%2'").arg(query1.value("tname").toString());
    query.exec(tc);
    query.first();
    QString pic=QString("image/%1.jpg").arg(query.value("tid").toString());
    QPixmap *pixmap=new QPixmap(pic);
    pixmap->scaled(ui->teacherpic->size(),Qt::KeepAspectRatio);
    ui->teacherpic->setScaledContents(true);
    ui->teacherpic->setPixmap(*pixmap);

    QString as=QString("SELECT * FROM selectedlesson WHERE cid='%1' AND sid='%2'").arg(curId).arg(user);
    query.clear();
    query.exec(as);
    query.first();
    if (query.value("is_assessed").toString()=="1")   //已评教
    {
        ui->score_1->setText(query.value("tscore1").toString());
        ui->score_2->setText(query.value("tscore2").toString());
        ui->score_3->setText(query.value("tscore3").toString());
        ui->score_4->setText(query.value("tscore4").toString());
        ui->commentEdit->setText(query.value("comment").toString());
        return;
    }
    ui->score_1->clear();
    ui->score_2->clear();
    ui->score_3->clear();
    ui->score_4->clear();
    ui->commentEdit->clear();
}

void StudentWidget::on_assessSub_clicked()  //提交评教
{
    QSqlQuery query;
    QString curLesson=ui->assessbox->currentText();
    if (curLesson=="")
    {
        QMessageBox::information(this,"温馨提示","请选择评教课程！");
        ui->teacherpic->clear();
        ui->score_1->clear();
        ui->score_2->clear();
        ui->score_3->clear();
        ui->score_4->clear();
        ui->commentEdit->clear();
        ui->tcName->clear();
        ui->tcLesson->clear();
        return;
    }

    QString tc=QString("SELECT * FROM class_table WHERE cname='%1'").arg(curLesson);
    query.exec(tc);
    qDebug()<<"tc1："<<tc;
    query.first();

    QString recId=query.value("cid").toString();
    qDebug()<<"Id："<<recId;
    query.clear();
    tc=QString("SELECT * FROM selectedlesson WHERE cid='%1'").arg(recId);
    query.exec(tc);
    qDebug()<<"tc2："<<tc;
    if (!query.first())  //被退掉了
    {
        QMessageBox::information(this,"温馨提示","你未选该门课程！");
        ui->teacherpic->clear();
        ui->score_1->clear();
        ui->score_2->clear();
        ui->score_3->clear();
        ui->score_4->clear();
        ui->commentEdit->clear();
        ui->tcName->clear();
        ui->tcLesson->clear();
        return;
    }

    query.clear();
    tc=QString("SELECT * FROM class_table WHERE cname='%1'").arg(curLesson);
    query.exec(tc);
    query.first();
    if (query.value("is_open").toString()=="0")  //未开放评教
    {
        QMessageBox::information(this,"温馨提示","该课程评教尚未开始！");
        ui->teacherpic->clear();
        ui->score_1->clear();
        ui->score_2->clear();
        ui->score_3->clear();
        ui->score_4->clear();
        ui->commentEdit->clear();
        ui->tcName->clear();
        ui->tcLesson->clear();
        return;
    }

    QString curId=query.value("cid").toString();
    QString as=QString("SELECT * FROM selectedlesson WHERE cid='%1' AND sid='%2'").arg(curId).arg(user);
    query.clear();
    query.exec(as);
    query.first();
    if (query.value("is_assessed").toString()=="1")   //已评教
    {
        QMessageBox::information(this,"温馨提示","不可重复评教！");
        return;
    }
    if (ui->score_1->text()==""||ui->score_2->text()==""||ui->score_3->text()==""||ui->score_4->text()=="")
    {
        QMessageBox::information(this,"温馨提示","评教分数不能为空！");
        return;
    }

    int s1=ui->score_1->text().toInt();
    int s2=ui->score_2->text().toInt();
    int s3=ui->score_3->text().toInt();
    int s4=ui->score_4->text().toInt();
    if (s1<0||s1>15||s2<0||s2>30||s3<0||s3>25||s4<0||s4>30)
    {
        QMessageBox::information(this,"温馨提示","请输入合法分数！");
        return;
    }
    QString ss1=ui->score_1->text();
    QString ss2=ui->score_2->text();
    QString ss3=ui->score_3->text();
    QString ss4=ui->score_4->text();
    bool ok1=false,ok2=false,ok3=false,ok4=false;
    double val1=ss1.toDouble(&ok1);
    double val2=ss2.toDouble(&ok2);
    double val3=ss3.toDouble(&ok3);
    double val4=ss4.toDouble(&ok4);
    if (!ok1||!ok2||!ok3||!ok4)
    {
        QMessageBox::information(this,"温馨提示","请输入合法分数！");
        return;
    }
    QString com=ui->commentEdit->toPlainText();
    query.clear();
    as=QString("UPDATE selectedlesson SET tscore1=%1,tscore2=%2,tscore3=%3,tscore4=%4,comment='%5',is_assessed='%6',tscore='%7' WHERE sid='%8' AND cid='%9'").arg(s1).arg(s2).arg(s3).arg(s4).arg(com).arg(1).arg(s1+s2+s3+s4).arg(user).arg(curId);
    query.exec(as);
    QMessageBox::information(this,"温馨提示","评教成功！");
}

void StudentWidget::on_checkPic_clicked()
{
    scorePic *sp=new scorePic(NULL,user);
    sp->show();
}

void StudentWidget::on_checkFinish_clicked()
{
    scoreFinish *sf=new scoreFinish(NULL,user);
    sf->show();
}


void StudentWidget::on_newsBtn_clicked()
{
    announcepage_teacher *at=new announcepage_teacher();
    at->show();
}


void StudentWidget::on_checkClass_clicked()
{
    ClassTable *ct=new ClassTable(NULL,user);
    ct->show();
}


void StudentWidget::on_exportScore_clicked()
{
    QString filepath=QFileDialog::getSaveFileName(this,tr("Save as..."),QString(),tr("EXCEL files (*.xls *.xlsx)"));

    QFile file(filepath);
    if (!file.open(QFile::WriteOnly|QIODevice::Text))
    {
        //QMessageBox::warning(this,tr("Error"),tr("文件未打开！"));
        return;
    }

    int row=ui->scoreReview->model()->rowCount();
    int col=ui->scoreReview->model()->columnCount();
    QList<QString> list;

    //添加列标题
    QString HeaderRow;
    for (int i=0;i<col;i++)
    {
        HeaderRow.append((ui->scoreReview->model()->headerData(i,Qt::Horizontal)).toString());
        HeaderRow.append("\t");
    }
    qDebug()<<HeaderRow;
    qDebug()<<"row:"<<row<<"  col:"<<col;

    list.push_back(HeaderRow);
    for (int i=0;i<row;i++)
    {
        QString rowStr="";
        for (int j=0;j<col;j++)
        {
            QModelIndex index=ui->scoreReview->model()->index(i,j);
            if (ui->scoreReview->model()->data(index)==NULL)
                rowStr.append("\t");
            else
            {
                QString s=ui->scoreReview->model()->data(index).toString();
                rowStr.append(s+"\t");
            }
        }
        list.push_back(rowStr);
    }
    //将表格内容添加到富文本中
    QTextEdit textEdit;
    for (int i=0;i<list.size();i++)
        textEdit.append(list.at(i));

    //写入文件中
    QTextStream ts(&file);
    ts<<textEdit.document()->toPlainText();
    file.close();
    QMessageBox::information(this,"温馨提示","导出成功！");
}


void StudentWidget::on_quitBtn_clicked()
{
    this->close();
    LoginDialog *ld=new LoginDialog(NULL);
    ld->show();
}



void StudentWidget::on_helpBtn_clicked()
{
    helpwidget *hw=new helpwidget();
    hw->show();
}


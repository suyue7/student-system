#include "scoreinputdialog.h"
#include "ui_scoreinputdialog.h"

ScoreInputDialog::ScoreInputDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreInputDialog)
{
    ui->setupUi(this);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    model = new QStandardItemModel();
    ui->tableView->setModel(model);
    /*设置列字段名*/
    QStringList headers;
    headers << "学号" << "姓名" << "性别" << "院系"<< "成绩";
    model->setHorizontalHeaderLabels(headers);
    //设置只有“成绩”栏可编辑
    for(int i = 0; i < model->rowCount(); i++){
        for(int j = 0 ; j < model->columnCount()-1; j++){
            model->item(i, j)->setEditable(false);
        }
    }

}
void ScoreInputDialog::setmodel()
{
        qDebug()<<"选中的课程id2" << selectedLessonID;
                QString sql=QString("SELECT student_table.sid,student_table.sname,student_table.ssex,student_table.sdepartment,sscore FROM score_table, student_table WHERE cid='%1' AND score_table.sid = student_table.sid;").arg(selectedLessonID);
        QSqlQuery query;
        if(query.exec(sql))
        {
            qDebug()<<"进入登记页面成功";
        }
        else{
            qDebug()<<"执行登记页面失败";
        }
        while(query.next()){
            qDebug() << "success!";
            QString no=query.value("sid").toString();
            QString name=query.value("sname").toString();
            QString sex=query.value("ssex").toString();
            QString dep=query.value("sdepartment").toString();
            QString score=query.value("sscore").toString();

            QList<QStandardItem*> itemlist;
            itemlist << new QStandardItem(no) << new QStandardItem(name) << new QStandardItem(sex) << new QStandardItem(dep) << new QStandardItem(score);
            model->appendRow(itemlist);
        }
}
ScoreInputDialog::~ScoreInputDialog()
{
    delete ui;
}

void ScoreInputDialog::on_browseradioButton_clicked()
{
    if(ui->browseradioButton->isChecked()){
        ui->browseradioButton->setText("输入状态");
        ui->exitpushButton->setText("保存并退出");
        inputFlag = true;
        ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);  //单元格双击可编辑
        //设置只有“成绩”栏可编辑
        for(int i = 0; i < model->rowCount(); i++){
            for(int j = 0 ; j < model->columnCount()-1; j++){
                model->item(i, j)->setEditable(false);
            }
        }
    }else{
        ui->browseradioButton->setText("浏览状态");
        ui->exitpushButton->setText("放弃并退出");
        inputFlag = false;
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}
bool ScoreInputDialog::updateLessonScore(){
    if(!inputFlag)
        return true;
    QString stunum;
    QString uscore;
    QModelIndex index;
    QSqlQuery query;
    for(int i=0;i<model->rowCount();i++){
        stunum = model->data(model->index(i,0)).toString();
        uscore = model->data(model->index(i,4)).toString();
        std::string r = uscore.toStdString();
        std::regex reg("[1-9]\\d{1,2}");
        bool bValid=std::regex_match(r, reg);
        if(bValid){
            QString updateSql = QString("UPDATE score_table SET sscore='%1' WHERE sid='%2'").arg(uscore).arg(stunum);
            if(query.exec(updateSql)){qDebug()<<"成绩更新成功";};
        }else{
            QMessageBox::warning(this, "警告", "学生成绩是0-100之间的数字！请重新输入");
            return false;
        }
    }
    return true;
}

void ScoreInputDialog::loadLessonScore(){
    QString sql=QString("SELECT student_table.sid,student_table.sname,student_table.ssex,student_table.sdepartment,sscore FROM score_table, student_table WHERE cid='%1' AND score_table.sid = student_table.sid").arg(selectedLessonID);
    model->removeRows(0,model->rowCount()); //删除所有行
    QSqlQuery query;
    query.exec(sql);
    while(query.next()){
        QString no=query.value("sid").toString();
        QString name=query.value("sname").toString();
        QString sex=query.value("ssex").toString();
        QString dep=query.value("sdepartment").toString();
        QString score=query.value("sscore").toString();

        QList<QStandardItem*> list;
        list << new QStandardItem(no) << new QStandardItem(name) << new QStandardItem(sex) << new QStandardItem(dep) << new QStandardItem(score);
        model->appendRow(list);
    }
    ui->tableView->setModel(model);
}

QString ScoreInputDialog::getLessonId(QString lvstr){
    int endp = lvstr.indexOf(']');
    return lvstr.mid(1, endp-1).trimmed();
}

void ScoreInputDialog::on_exitpushButton_clicked()
{
    if(updateLessonScore())
        close();
}


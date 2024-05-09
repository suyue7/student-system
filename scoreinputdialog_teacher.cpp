#include "scoreinputdialog_teacher.h"
#include "ui_scoreinputdialog_teacher.h"
#include "mainwindow.h"

ScoreInputDialog_teacher::ScoreInputDialog_teacher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreInputDialog_teacher)
{
    ui->setupUi(this);

    ui->label_2->lower();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    loadTeacherLesson();
    QString tiplb = QString("（教师：%1 ）请选择课程：").arg(MainWindow::sfName);
    ui->tiplabel->setText(tiplb);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->comboBox->addItems(lessData);
    ui->comboBox->setEditable(false);

    model = new QStandardItemModel();
    ui->tableView->setModel(model);

    /*设置列字段名*/
    QStringList headers;
    headers << "学号" << "姓名" << "性别" << "院系"<< "成绩";
    model->setHorizontalHeaderLabels(headers);

    selectedLessonID = getLessonId(ui->comboBox->currentText());
    qDebug() << selectedLessonID;
    QString sql=QString("SELECT student_table.sid,student_table.sname,student_table.ssex,student_table.sdepartment,sscore FROM score_table, student_table WHERE score_table.cid='%1' AND score_table.sid = student_table.sid;").arg(selectedLessonID);
    QSqlQuery query;
    query.exec(sql);
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
    //设置只有“成绩”栏可编辑
    for(int i = 0; i < model->rowCount(); i++){
        for(int j = 0 ; j < model->columnCount()-1; j++){
            model->item(i, j)->setEditable(false);
        }
    }
}

ScoreInputDialog_teacher::~ScoreInputDialog_teacher()
{
    delete ui;
}

void ScoreInputDialog_teacher::on_browseradioButton_clicked()
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

void ScoreInputDialog_teacher::on_comboBox_activated()
{
    QString curlesson = getLessonId(ui->comboBox->currentText());
    if(curlesson != selectedLessonID){
        if(selectedLessonID.length() != 0)
            updateLessonScore(); //  更换课程，要先保存原先课程录入数据
        selectedLessonID = curlesson;
        loadLessonScore();
    }
}

void ScoreInputDialog_teacher::loadTeacherLesson(){
    QString sql = QString("SELECT cid, cname FROM class_table WHERE tid='%1';").arg(MainWindow::sfID);
    QSqlQuery lesson;
    lesson.exec(sql);
    while(lesson.next()){
        QString no = lesson.value("cid").toString();
        QString name = lesson.value("cname").toString();
        lessData.append(QString("[%1] %2").arg(no, name));
    }
}

bool ScoreInputDialog_teacher::updateLessonScore(){
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
            QString updateSql = QString("UPDATE score_table SET sscore=%1 WHERE cid='%2' AND sid='%3'").arg(uscore,selectedLessonID,stunum);
            query.exec(updateSql);
        }else{
            QMessageBox::warning(this, "警告", "学生成绩是0-100之间的数字！请重新输入");
            return false;
        }
    }
    return true;
}

void ScoreInputDialog_teacher::loadLessonScore(){
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

QString ScoreInputDialog_teacher::getLessonId(QString lvstr){
    int endp = lvstr.indexOf(']');
    return lvstr.mid(1, endp-1).trimmed();
}

void ScoreInputDialog_teacher::on_exitpushButton_clicked()
{
    if(updateLessonScore())
        close();
}


void ScoreInputDialog_teacher::on_exportpushButton_clicked()
{
    if(inputFlag){
        QMessageBox::warning(this, "Warning", "输入状态下不可导出学生成绩！");
        return;
    }else{
        QString filepath = QFileDialog::getSaveFileName(this, tr("Save as..."),QString(), tr("EXCEL files (*.xls *.xlsx)"));

        int row =model->rowCount();
        int col = model->columnCount();
        QList<QString> list;
        //添加列标题
        QString HeaderRow;
        for (int i = 0; i<col; i++)
        {
            HeaderRow.append(model->horizontalHeaderItem(i)->text() + "\t");
        }
        list.push_back(HeaderRow);
        for (int i = 0; i<row; i++)
        {
            QString rowStr = "";
            for (int j = 0; j<col; j++)
                rowStr += model->item(i, j)->text() + "\t";
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
}


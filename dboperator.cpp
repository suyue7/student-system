#include "dboperator.h"

DBOperator::DBOperator()
{   openFlag = false; }

void DBOperator::DBOpen()
{   QString dsn;
    if(!openFlag)
    {
        dbcon = QSqlDatabase::addDatabase("QODBC");  // ODBC 驱动
        dbcon.setHostName("127.0.0.1");              // MySQL 服务器ip地址，本机
        dbcon.setPort(3306);                         // 端口号，默认
        dbcon.setDatabaseName("persondb");           // ODBC 数据源名称
        bool ok = dbcon.open();
        if(!ok)
            qDebug() << "Error,  数据库文件打开失败！";
        else{
            qDebug()<<"打开数据库成功";
        }
        openFlag = true;

    }
}

void DBOperator::DBClose()
{   openFlag = false;
    dbcon.close();
}

QSqlQuery DBOperator::DBGetData(QString sqlstr, bool &sucessFlag)
{   QSqlQuery query = QSqlQuery(dbcon);
    sucessFlag = query.exec(sqlstr);
    return query;
}

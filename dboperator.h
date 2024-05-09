#ifndef DBOPERATOR_H
#define DBOPERATOR_H

#include <QtSql/QSqlDatabase>
#include <QStringList>
#include <QtSql/QSqlQuery>
#include <QDebug>

class DBOperator
{
private:
    QSqlDatabase dbcon;//定义静态变量db数据库实例
    bool openFlag;
public:
    DBOperator();
    void DBOpen();
    void DBClose();
    QSqlQuery DBGetData(QString sqlstr, bool &sucessFlag);//获得数据库链接
};

#endif // DBOPERATOR_H

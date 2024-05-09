#ifndef DATABASECONECTION_H
#define DATABASECONECTION_H
#include <QSqlDatabase>
void connectdb(QSqlDatabase& db){
    //连接数据库(加载数据库驱动，返回数据库对象)
    db = QSqlDatabase::addDatabase("QODBC");   //加载MySQL数据库驱动，返回数据库对象
    db.setDatabaseName("persondb");
    db.setHostName("localhost");
    db.setPort(3306);
}
#endif // DATABASECONECTION_H

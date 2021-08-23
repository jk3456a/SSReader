#include<QtSql>
#include"global.h"
#include"sqltool.h"


void init_sql(){
    if(QSqlDatabase::contains("qt_sql_default_connection"))
       db = QSqlDatabase::database("qt_sql_default_connection");
    else
    db= QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(Ip);    //数据库主机名
    db.setPort(Port);
    db.setDatabaseName("test");    //数据库名
    db.setUserName(MysqlUser);        //数据库用户名
    db.setPassword(MysqlPass);        //数据库密码
}


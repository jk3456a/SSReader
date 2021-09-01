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

//0只要前面，1要所有
QString reformatDate(QString *date, int num) {
        QMap<QString, QString> s2month = {
            {"Jan", "01"},
            {"Feb", "02"},
            {"Mar", "03"},
            {"Apr", "04"},
            {"May", "05"},
            {"Jun", "06"},
            {"Jul", "07"},
            {"Aug", "08"},
            {"Sep", "09"},
            {"Oct", "10"},
            {"Nov", "11"},
            {"Dec", "12"}
        };
        QStringList strList = date->split(" ");
        QString month = strList[1];
        month = s2month[month];
        if(num == 0){
            return strList[2] + month + strList[0];
        } else
        return strList[2] + "-" + month + "-" + strList[0] +  " " + strList[3];
    }


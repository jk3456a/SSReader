#include "global.h"

QString Ip = "120.53.118.220";
QString MysqlUser = "root";
QString MysqlPass = "8^7vu^VrPUab";
QString LogUser = "";
QString LogPass = "";
QString Loguid = "";
int Port = 3306;
QVariantList ArticleList;
QVariantList UserList;
QSqlDatabase db;

QUrl url;
QNetworkRequest req;
QNetworkReply *reply;
QNetworkAccessManager *manager;
QStringList Routelist;

extern const QString load_src = "select cid,source,rssurl from subscribe where uid = ? order by cid,source";
extern const QString load_rssurl = "select rssurl from subscribe where(uid = ?)";
extern const QString load_all_article = "select title,pubdate,aurl from article where(uid = ?)and(rssurl = ?)";
extern const QString insert_src = "insert into subscribe(uid,source,rssurl) values(?,?,?)";
extern const QString insert_art = "insert into article(aid,title,pubdate,aurl,rssurl,uid) values (?,?,?,?,?,?)";
extern const QString read_art = "update article set onread = ? where uid = ? ";
extern const QString star_art = "update article set onstar = ? where uid = ? ";
extern const QString wait_art = "update article set onwait = ? where uid = ? ";

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

extern const QString load_src = "select cid,source,rssurl from subscribe where uid = ? order by cid,source";
extern const QString load_overview = "select rssurl from subscribe where(uid = ?)and((cid = ?)or(source = ?)or(rssurl = ?))";
extern const QString insert_src = "insert into subscribe(uid,source,rssurl) values(?,?,?)";
extern const QString insert_art = "insert into article(aid,aurl,uid) values (?,?,?)";
extern const QString read_art = "update article set onread = ? where uid = ? ";
extern const QString star_art = "update article set onstar = ? where uid = ? ";
extern const QString wait_art = "update article set onwait = ? where uid = ? ";

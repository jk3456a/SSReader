#define view_all 0
#define view_unread 1
#define view_star 2
#define view_wait 3

#ifndef GLOBAL_H
#define GLOBAL_H
#include "pch.h"

extern QString Ip;
extern QString MysqlUser;
extern QString MysqlPass;
extern QString LogUser;
extern QString LogPass;
extern QString Loguid;
extern int Port;
extern QVariantList ArticleList;
extern QVariantList UserList;

extern QSqlDatabase db;
extern QSqlQuery *query;

extern const QString load_src;
extern const QString load_overview;
extern const QString insert_src;
extern const QString insert_art;
extern const QString read_art;
extern const QString star_art;
extern const QString wait_art;

#endif // GLOBAL_H

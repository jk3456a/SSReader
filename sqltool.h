#ifndef SQLTOOL_H
#define SQLTOOL_H

#include <QtSql>
#include "global.h"
#include <iostream>

extern void init_sql();
extern QString reformatDate(QString *date, int num);
#endif // SQLTOOL_H

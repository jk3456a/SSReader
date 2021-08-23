#include "loginpage.h"
#include "global.h"
#include "sqltool.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    init_sql();
    LoginPage w;
    w.setWindowTitle("登录界面");
    w.show();
    return a.exec();
}

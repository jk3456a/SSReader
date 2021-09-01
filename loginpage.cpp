#include "loginpage.h"

LoginPage::LoginPage(QWidget *parent) : QWidget(parent)
{
    //登录界面格式化

    //layout声明加this,就是最底层的layout
    //以下命令相当于 this->setlayout(Layout);

    //发生Layout错误；错误原因：某些变量没有实例化

    QFormLayout * VLayout2 = new QFormLayout();
    UserLine = new QLineEdit;
    PasswordLine = new QLineEdit;
    UserLine->setText("yummy");
    PasswordLine->setText("123456");
    PasswordLine->setEchoMode(QLineEdit::Password);

    VLayout2->addRow(tr("&Name:"),UserLine);
    VLayout2->addRow(tr("&Password:"),PasswordLine);
    VLayout2->setLabelAlignment(Qt::AlignRight);

    QHBoxLayout * VLayout3 = new QHBoxLayout();
    LoginButton = new QPushButton(tr("Log in"),this);
    SignUpButton = new QPushButton(tr("Sign up"),this);
    VLayout3->addWidget(LoginButton);
    VLayout3->addWidget(SignUpButton);

    QVBoxLayout * Layout = new QVBoxLayout(this);
    QLabel * TitleImage = new QLabel;
    Layout->addWidget(TitleImage);
    Layout->addLayout(VLayout2);
    Layout->addLayout(VLayout3);
    Layout->setSpacing(10);
    Layout->setMargin(20);

    LoginButton->setShortcut(tr("return"));

    //连接槽函数
    connect(LoginButton, SIGNAL(clicked()), this, SLOT(log_in()));
    connect(SignUpButton,SIGNAL(clicked()),this,SLOT(sign_up()));

    //以下命令connect失败,原因竟然在大小写，omg
    //connect(LoginButton,signal(clicked()),this ,SLOT(login()));

}

LoginPage::~LoginPage()
{
}

void LoginPage::log_in(){
    //获得数据
    QString User = UserLine->text() ;
    QString Pass = PasswordLine->text();

    //连接数据库
    if(!db.open()){
        qDebug()<<"sql open error";
        db.close();
    }

    //登录验证
    QSqlQuery *query = new QSqlQuery(db);
    if(query->exec("select id,username,password from admin")){
        qDebug()<<"access admin successfully";
    }else{
        qDebug()<<"fail to access admin";
    }

    bool T1=false;
    while(query->next())
    {
        QString uid = query->value(0).toString();
        QString user = query->value(1).toString();
        QString pass = query->value(2).toString();
        //qDebug() << user << pass ;
        if(User.compare(user)==0&&Pass.compare(pass)==0)
        {
            LogUser=User;
            LogPass=Pass;
            Loguid=uid;
            T1=true;
            this->hide();
            SSReader=new MainWindow();
            SSReader->show();
        }
    }

     if (T1 == false){
         QMessageBox::information(this, "Warning", "用户名或密码错误");
     }

     delete query;
     db.close();
}

void LoginPage::sign_up(){
    //获得数据
    QString User = UserLine->text() ;
    QString Pass =PasswordLine->text();
    //链接数据库,传入新注册用户
    if(!db.open()){
        qDebug()<<"sql open error";
        db.close();
    }
    QSqlQuery *query = new QSqlQuery(db);
    QUuid uuid = QUuid::createUuid();
    QString uid = uuid.toString();
    uid.remove("{").remove("}").remove("-");
    QString sql = QString("insert into admin(id,username,password) values ('%1','%2','%3')").arg(uid).arg(User).arg(Pass);
    if(!query->exec(sql)){
        QMessageBox::information(this, "警告", "注册失败");
    }else{
        this->update();
    }

    delete query;
    db.close();
}




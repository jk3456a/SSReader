#include "subspage.h"
#include "ui_subspage.h"


SubsPage::SubsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubsPage)
{
    ui->setupUi(this);
    //请求json
    s_network= new Internet();
    s_network->loadJson(QUrl("http://120.53.118.220:1200/api/routes"),&Routelist);
    qDebug()<<"下面是routes:"<<"\n"<<Routelist;
    //设置自动补全

    QCompleter *completer = new QCompleter(Routelist, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->SubLine->setCompleter(completer);
}

SubsPage::~SubsPage()
{
    delete ui;
}


void SubsPage::on_SubButton_clicked()
{
    QString Rssurl = ui->SubLine->text();
    if(Rssurl!=NULL){
        QString Source = Rssurl;
        Rssurl="http://120.53.118.220:1200/"+Rssurl;
        //qDebug()<<"这是rssurl"<<Rssurl;
        Source = Source.split("/").first();
        //qDebug()<<"这是source"<<Source;
        if(!db.isOpen()){
            db.open();
        }
        //qDebug()<<db.isOpen();
        QSqlQuery *query = new QSqlQuery(db);
        query->prepare(insert_src);
        query->addBindValue(Loguid);
        query->addBindValue(Source);
        query->addBindValue(Rssurl);

        if(!query->exec()){
            qDebug()<<"insert error";
        }else {
            QMessageBox::information(this,"提醒","添加订阅成功");
        }
        delete query;
    }else {
        QMessageBox::information(this,"警告","不能添加空白订阅");
    }

}


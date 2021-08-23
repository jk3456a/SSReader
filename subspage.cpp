#include "subspage.h"
#include "ui_subspage.h"


SubsPage::SubsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubsPage)
{
    ui->setupUi(this);
    //请求json
    httpRequest(QUrl("https://rsshub.app/api/routes/sspai%7Cmatrix"));
    //qDebug()<<Routelist;
    //设置自动补全
    QCompleter *completer = new QCompleter(Routelist, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->SubLine->setCompleter(completer);
}

SubsPage::~SubsPage()
{
    delete ui;
}

void SubsPage::httpRequest(const QUrl &requestedUrl){
    url = requestedUrl;
    manager = new QNetworkAccessManager();

    // https需要的配置（http不需要）
    QSslConfiguration sslConf = req.sslConfiguration();
    sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConf.setProtocol(QSsl::TlsV1SslV3);
    req.setSslConfiguration(sslConf);
    // https需要的配置（http不需要）

    req.setUrl(url);
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    req.setRawHeader("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
    req.setRawHeader("User-Agent","Mozilla/5.0 (Windows NT 10.0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/86.0.4240.198 Safari/537.36");
    reply = manager->get(req);
    connect(manager,SIGNAL(finished(QNetworkReply*)), this,SLOT(replyFinished(QNetworkReply*)));

}

void SubsPage::replyFinished(QNetworkReply*){
    // <1>判断有没有错误
   if (reply->error()){
       qDebug()<<reply->errorString();
       reply->deleteLater();
       return;
   }

   // <2>检测状态码
   int statusCode  = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
   qDebug() << "statusCode:" << statusCode;

   // <3>判断是否需要重定向
   if (statusCode >= 200 && statusCode <300){
       // 准备读数据

       // 防止中文乱码
       //QTextCodec *codec = QTextCodec::codecForName("utf8");

        QByteArray str = reply->readAll();
        if (str.isEmpty()){
            qDebug()<<"replystring is empty!";
        }
        // 解析Json字符串
        QJsonParseError error;
        QJsonDocument JsonDoc = QJsonDocument::fromJson(str, &error);

        // 字符串没有错误
        if (!JsonDoc.isEmpty() && (error.error == QJsonParseError::NoError)) {
            // 转为Json对象
            const QJsonObject JsonObj = JsonDoc.object();
            QJsonObject data = JsonObj.value("data").toObject();
            // 迭代获得route词典
            QJsonObject::iterator it;
            for(it=data.begin();it!=data.end();it++){
                QJsonArray routes = it.value().toArray();
                for(int i = 0; i < data.count(); i++){
                    QJsonValue value = routes.at(i);
                    Routelist += value.toString();
                }
            }
        }else {
            qDebug()<<"JsonDoc translate error";
        }
        reply->deleteLater();
        reply = nullptr;
    }
   else if (statusCode >=300 && statusCode <400) {
       // 获取重定向信息
       const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
       // 检测是否需要重定向，如果不需要则读数据
       if (!redirectionTarget.isNull()) {
           const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());

           reply->deleteLater();
           reply = nullptr;

           httpRequest(redirectedUrl);
           qDebug()<< "http redirect to " << redirectedUrl.toString();
           return;
       }
   }
}
void SubsPage::on_SubButton_clicked()
{
    QString Rssurl = ui->SubLine->text().trimmed();
    if(Rssurl!=NULL){
        QString Source = Rssurl;
        Rssurl="https://rsshub.app/api/routes"+Rssurl;
        Source.remove(0,1);
        int i = Source.indexOf("/");
        Source.remove(i);
        if(!db.isOpen()){
            db.open();
        }
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


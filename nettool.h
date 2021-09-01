#ifndef INTERNET_H
#define INTERNET_H

#include <QObject>
#include <QTimer>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

typedef struct {
    int httpCode;
    QByteArray response;
} httpReply_t;

class NetTool : public QObject
{
    Q_OBJECT
public:
    explicit NetTool(QObject *parent = nullptr);
    ~NetTool();
    bool loadJson(const QUrl &requestUrl, QStringList *Routelist);
    void loadXml(const QUrl &requestUrl, QString *XmlContent);
    //QString FindTitle(const QString sUrl);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    int httpRequest(const QUrl &requestUrl, httpReply_t *reply);
};

#endif // INTERNET_H

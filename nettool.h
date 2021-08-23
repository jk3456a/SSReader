#ifndef NETTOOL_H
#define NETTOOL_H

#include"pch.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTextCodec>

extern QString httpRequest(const QUrl &requestedUrl);
extern QStringList explainReply(const QString reply);

#endif // NETTOOL_H

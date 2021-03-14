#ifndef INDICEUV_H
#define INDICEUV_H

#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <apijson.h>


class IndiceUV:public APIJson
{
    Q_OBJECT
public:
    IndiceUV();

    QHash <QString, QVariant> readJson();

};

#endif // INDICEUV_H

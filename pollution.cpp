#include "pollution.h"
#include "apijson.h"
#include "define_url.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>


Pollution::Pollution()
{
    setRequest(URL_POLLUTION);
    connect(m_manager,&QNetworkAccessManager::finished,this,&Pollution::replyFinished);
}

QVariantHash Pollution::readJson()
{
    QJsonDocument d = QJsonDocument::fromJson(m_req);
    QJsonObject obj = d.object();
    QHash <QString, QVariant> hash;

    /*Récupérer les valeurs des polluants WAQI*/
    QJsonObject obj2 = obj["data"].toObject();
    hash["AQI"]=(obj2.value("aqi").toDouble());

    return hash;
}



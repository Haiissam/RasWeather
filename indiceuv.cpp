#include "indiceuv.h"
#include "apijson.h"
#include "define_url.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>


IndiceUV::IndiceUV()
{

    setRequest(URL_UV);
    connect(m_manager,&QNetworkAccessManager::finished,this,&IndiceUV::replyFinished);

}

QHash <QString, QVariant> IndiceUV::readJson()
{
    /*Récupérer les valeurs de l'indice UV*/
    QJsonDocument d = QJsonDocument::fromJson(m_req);
    QJsonObject obj = d.object();
    QVariantHash hash;
    hash["UV"]=obj.value("value").toDouble();

    return hash;
}



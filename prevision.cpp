#include "prevision.h"
#include "apijson.h"
#include "define_url.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariantHash>
#include <QJsonObject>

Prevision::Prevision()
{
    setRequest(URL_PREVISION);
    connect(m_manager,&QNetworkAccessManager::finished,this,&Prevision::replyFinished);
}

QHash<QString, QVariant> Prevision::readJson()

{
    QHash <QString, QVariant> hash;

    /*Récupérer les valeurs de coord (lat el lon)*/
    QJsonDocument d = QJsonDocument::fromJson(m_req);
    QJsonObject obj = d.object();

    QJsonArray tableauJSON;
    tableauJSON = obj["list"].toArray();

    for (int i = 0; i < tableauJSON.size(); i++) {

        /*Récupération des info dans l'objet main*/

        QJsonObject obj2 = tableauJSON[i].toObject();
        QJsonValue val = obj2.value(QString("main"));
        QJsonObject item = val.toObject();
        hash[QString ("Temp%1").arg(i)]=item.value("temp").toDouble();
        hash[QString ("Humidité%1").arg(i)] = item.value("humidity").toDouble();

        /*Récupération des info dans l'array weather*/

        QJsonArray tab = obj2["weather"].toArray();
        QJsonObject obj3 = tab[0].toObject();
        hash[QString ("Main%1").arg(i)]=obj3.value("main").toString();
        hash[QString ("Description%1").arg(i)] = obj3.value("description").toString();
        hash[QString ("Icon%1").arg(i)] = obj3.value("icon").toString();


        hash[QString ("Date_heure%1").arg(i)] = obj2.value("dt_txt").toString();

        /*Récupération de la quantité de pluie tombé sur les 3 dernières heures en mm*/

        QJsonObject obj4 = tableauJSON[i].toObject();
        QJsonValue val1 = obj2.value(QString("rain"));
        QJsonObject item1 = val1.toObject();
        hash[QString ("Rain%1").arg(i)]=item1.value("3h").toDouble();
    }

    return hash;
}



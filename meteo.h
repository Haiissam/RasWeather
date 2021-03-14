#ifndef METEO_H
#define METEO_H

#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <apijson.h>


class meteo:public APIJson
{
     Q_OBJECT

public:
    meteo();
    QVariantHash readJson();

};



#endif // METEO_H

#ifndef POLLUTION_H
#define POLLUTION_H

#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <apijson.h>

class Pollution:public APIJson
{

    Q_OBJECT

public:   
    Pollution();
    QVariantHash readJson();

};

#endif // POLLUTION_H

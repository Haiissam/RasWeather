#ifndef PREVISION_H
#define PREVISION_H

#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <apijson.h>

class Prevision:public APIJson
{

    Q_OBJECT

public:
    Prevision();

    QHash <QString, QVariant> readJson();

};

#endif // PREVISION_H

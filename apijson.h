#ifndef APIJSON_H
#define APIJSON_H

#include <QMainWindow>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>
using namespace std;

class APIJson:public QObject
{
    Q_OBJECT
public:
    APIJson();
    ~APIJson();

    void setRequest(QString turl);
    virtual QHash <QString, QVariant> readJson()=0;
    QHash <QString, QVariant> getHash() {return m_hash;}

protected:
    QNetworkReply *m_reply;
    QNetworkAccessManager *m_manager;
    QNetworkRequest m_request;
    QByteArray m_req;
    QHash <QString, QVariant> m_hash;


public slots:
   virtual void replyFinished();

signals:
   void received();
};

#endif // APIJSON_H



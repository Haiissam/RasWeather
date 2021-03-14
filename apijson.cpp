#include "apijson.h"
#include "define_url.h"

#include <string>
#include <QString>
using namespace std;

APIJson::APIJson()
{

}

APIJson::~APIJson()
{
    delete m_manager;
}

void APIJson::setRequest(QString turl)
{
    m_manager = new QNetworkAccessManager(this);
    QUrl url(turl);
    m_request.setUrl(url);
    m_reply = m_manager->get(m_request);
}

QHash<QString, QVariant> APIJson::readJson()
{
    return QHash<QString, QVariant>();
}

void APIJson::replyFinished()
{
    m_req = m_reply->readAll();
    m_hash = readJson();
    emit received();
}

#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QByteArray>
#include <QFile>
#include <QDataStream>
#include <QXmlStreamWriter>

class request : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString response READ response WRITE setresponse NOTIFY responseChanged)
public:
    QString m_response;
    QFile *m_file;
    QNetworkReply *m_reply;
    QString response(){
        return m_response;
    }
    void setresponse(const QString &response){
        if(response == m_response){
            return;
        }
        m_response = response;
        emit responseChanged();
    }
    request(){
        connect(this, &request::operate, this, &request::Request);
    }
public slots:
    void downloadProgress(qint64 Received, qint64 Total);
    void Request(const QString &paramater);
    void replyFinished(QNetworkReply *reply){
        setresponse((QString)reply->readAll());
        // QList<QByteArray> headerList = reply->rawHeaderList();
        // foreach(QByteArray head, headerList) {
        //     qDebug() << head << ":" << reply->rawHeader(head);
        // }
        // m_file->close();

        // QDomDocument versionXML;

        // if(!versionXML.setContent(data))
        // {
        //     qWarning() << "Failed to parse XML";
        // }
    }
signals:
    Q_INVOKABLE void operate(const QString &);
    void responseChanged();
    void finished();
};

#endif // TEST_H

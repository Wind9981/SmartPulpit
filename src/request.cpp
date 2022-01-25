#include "request.h"
#include <ctime>

int getTiet(int hour, int minute){
        switch (hour)
        {
                case 7:
                        if(minute >= 30)
                                return 1;
                        break;
                case 8:
                        if(minute <= 15)
                                return 1;
                        return 2;
                        break;
                case 9:
                        if(minute >= 0 && minute < 45)
                                return 3;
                        break;
                case 10:
                        if(minute >= 0 && minute < 45)
                                return 4;
                        return 5;
                        break;
                case 11:
                        if(minute <= 30)
                                return 5;
                        break;
                case 13:
                        if(minute >= 0 && minute < 45)
                                return 6;
                        return 7;
                        break;
                case 14:
                        if(minute <= 30)
                                return 7;
                        return 8;
                        break;
                case 15:
                        if(minute <= 15)
                                return 8;
                        return 9;
                        break;
                case 16:
                        if(minute <= 15)
                                return 9;
                        return 10;
                        break;
                
                default:
                        break;
        }

}

void request::downloadProgress(qint64 Received, qint64 Total){
        qDebug() << Received;
        qDebug() << Total;
        
        if(Received == Total){
                QByteArray dataByteArray = m_reply->readAll();
                QDataStream out(m_file);
                out << dataByteArray;
                emit finished();
        }
    }

void request::Request(const QString &parameter){
        qDebug() << "openSSL Version:" << QSslSocket::sslLibraryBuildVersionString();
        time_t now = time(0);
        tm *localTime = localtime(&now);
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        QNetworkRequest request;
        connect(manager, &QNetworkAccessManager::finished,
                this, &request::replyFinished);
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        //conf.setCaCertificates({});
        request.setSslConfiguration(conf);
        if(parameter == "https://192.168.1.102:5001/home/studentslist"){
                request.setUrl(QUrl(parameter));
                QNetworkReply *netReply = manager->get(request);
                QEventLoop loop;
                connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));
                loop.exec();
        }
        else if(parameter == "https://192.168.1.102:5001/home/allstudentsofstudy"){
                int tiet = getTiet(localTime->tm_hour, localTime->tm_min);
                // obj["Date_Of_Week"] = QString::number(localTime->tm_wday);
                // obj["Time"] = QString::number(tiet);
                request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                QString url = parameter;
                url.append(QString("?Date_Of_Week="));
                url.push_back(QString::number(2));
                url.push_back("&Time=");
                url.push_back(QString::number(3));
                request.setUrl(QUrl(url));
                qDebug() << url;
                QNetworkReply *netReply = manager->get(request);
                QEventLoop loop;
                connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));
                loop.exec();
                qDebug() << m_response;
        }else if(parameter == "https://192.168.1.102:5001/home/download"){
                request.setUrl(QUrl(parameter));
                m_reply = manager->get(request);
                QEventLoop loop;
                m_file = new QFile("/home/hoang/Desktop/file.odp");
                m_file->open(QIODevice::WriteOnly);
                connect(m_reply, &QNetworkReply::downloadProgress,this, &request::downloadProgress);
                connect(this, SIGNAL(finished()), &loop, SLOT(quit()));
                loop.exec();
                qDebug() << m_response;
        }else if(parameter == "https://192.168.1.102:5001/home/slideslist"){
                request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
                QString url = parameter;
                url.append(QString("?idteacher="));
                url.push_back(QString::number(1));
                request.setUrl(QUrl(url));
                qDebug() << url;
                QNetworkReply *netReply = manager->get(request);
                QEventLoop loop;
                connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));
                loop.exec();
                qDebug() << m_response;
        }
}

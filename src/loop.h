#ifndef WORKER2_H
#define WORKER2_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>

class Worker2 : public QObject
{
    Q_OBJECT

public slots:
    void doWork(const QString &parameter);

signals:
    void resultReady(const QString &result);
};

class EventLoop : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString number READ number WRITE setNumber NOTIFY numberChanged)
    QThread workerThread;
public:
    QString m_number;
    QString number(){
        return m_number;
    }
    void setNumber(const QString &number){
        if(number == m_number){
            return;
        }
        m_number = number;
        emit numberChanged();
    }
    EventLoop() {
        Worker2 *worker2 = new Worker2;
        worker2->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker2, &QObject::deleteLater);
        connect(this, &EventLoop::operate, worker2, &Worker2::doWork);
        connect(worker2, &Worker2::resultReady, this, &EventLoop::handleResults);
        workerThread.start();
    }
    ~EventLoop() {
        workerThread.quit();
        workerThread.wait();
    }
public slots:
    void handleResults(const QString &paramater){
        setNumber(paramater);
    }
signals:
    Q_INVOKABLE void operate(const QString &);
    void numberChanged();
};

#endif // WORKER_H

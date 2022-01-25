#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(const QString &parameter);

signals:
    void resultReady(const QString &result);
};

class FaceRegco : public QObject
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
    FaceRegco() {
        Worker *worker = new Worker;
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &FaceRegco::operate, worker, &Worker::doWork);
        connect(worker, &Worker::resultReady, this, &FaceRegco::handleResults);
        workerThread.start();
    }
    ~FaceRegco() {
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

#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include <QDebug>
#include <string>

class Presentation : public QObject
{
    Q_OBJECT
public:
    Presentation(){
        connect(this, &Presentation::operate, this, &Presentation::Present);
    }
public slots:
    void Present(const QString &paramater);
signals:
    Q_INVOKABLE void operate(const QString &);
    void numberChanged();
};

#endif // WORKER_H

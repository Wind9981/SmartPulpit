#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <facerecog.h>
#include <presentation.h>
#include <QTimer>
#include <request.h>
#include <iostream>
#include <loop.h>
//#include <QtWebEngine/qtwebengineglobal.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    EventLoop *eventLoop = new EventLoop;
    request *Request = new request;
    FaceRegco *faceRegco = new FaceRegco;
    Presentation *present = new Presentation;
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("_eventLoop", eventLoop);
    context->setContextProperty("_faceregco", faceRegco);
    context->setContextProperty("_request", Request);
    std::cout << "hello";
    context->setContextProperty("_present", present);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}

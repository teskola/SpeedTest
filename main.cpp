#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "speedtest.h"


int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qt/qml/sairaan_nopee/Main.qml"));
    QQmlContext* qmlContext = engine.rootContext();
    SpeedTest* speedTest = new SpeedTest{};
    qmlContext->setContextProperty("speedTest", speedTest);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    qmlRegisterType<SpeedTest>("SpeedTest", 1, 0,"SpeedTest");
    engine.load(url);
    return app.exec();
}

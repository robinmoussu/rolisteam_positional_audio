#include "mumbleplugin.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<MumblePlugin>("io.qt.examples.mumbleplugin", 1, 0, "MumblePlugin");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        cerr << "Root object not found" << endl;
        return -1;
    }

    QObject *application = engine.rootObjects().first();
    MumblePlugin m;
    QObject::connect(application, SIGNAL(adventurerPosition(double,double)), &m, SLOT(setPositionalAudio(double,double)));

    return app.exec();
}

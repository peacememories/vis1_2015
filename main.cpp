#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "volumetricview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<VolumetricView>("rendering", 1, 0, "VolumetricView");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

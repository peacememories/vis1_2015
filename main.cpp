#include <QApplication>
#include <QOpenGLDebugLogger>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QtQml>

#include "volumetricview.h"
#include "cameracontrol.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;// = window->format();
    format.setVersion(4,3);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setOption(QSurfaceFormat::DebugContext);
    QSurfaceFormat::setDefaultFormat(format);

    qmlRegisterType<VolumetricView>("rendering", 1, 0, "VolumetricView");
    qmlRegisterType<CameraControl>("rendering", 1, 0, "CameraControl");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

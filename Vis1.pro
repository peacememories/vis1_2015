TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    Volume.cpp \
    volumetricview.cpp \
    volumetricrenderer.cpp \
    camera.cpp \
    cameracontrol.cpp \
    openglloghandler.cpp

RESOURCES += qml.qrc \
    shaders.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Volume.h \
    volumetricview.h \
    volumetricrenderer.h \
    camera.h \
    cameracontrol.h \
    openglloghandler.h

CONFIG += c++11

DISTFILES += \
    cube.vsh \
    cube.fsh

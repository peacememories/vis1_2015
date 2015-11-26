#include <QtQuick>
#include "cameracontrol.h"

CameraControl::CameraControl()
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemAcceptsInputMethod, true);
}

void CameraControl::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "Mouse Event!";
}

void CameraControl::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Mouse Pressed!";
}



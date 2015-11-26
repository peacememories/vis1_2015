#include <QtQuick>
#include "cameracontrol.h"

inline float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}

CameraControl::CameraControl()
{
    setAcceptedMouseButtons(Qt::LeftButton);
    setFlag(ItemAcceptsInputMethod, true);
    m_rotation = 0;
    m_elevation = 45;
    m_distance = 3;
    updateDirection();
}

void CameraControl::updateDirection()
{
    QMatrix4x4 movement;
    movement.rotate(-m_rotation, QVector3D(0,1,0));
    movement.rotate(-m_elevation, QVector3D(1,0,0));

    m_direction = m_distance * (movement * QVector3D(0,0,1));

    directionChanged(m_direction);
}

void CameraControl::zoomWithPixels(QPoint dir)
{
    int distance = dir.y();

    float speed = 0.01;

    m_distance *= 1 - speed * distance;

    updateDirection();
}

void CameraControl::zoomWithSteps(QPoint dir)
{
    int steps = dir.y();

    float speed = 0.15;

    m_distance *= 1 - speed * steps;

    updateDirection();
}

void CameraControl::mouseMoveEvent(QMouseEvent *event)
{
    QPoint delta = event->pos() - m_lastPos;
    m_lastPos = event->pos();

    float xspeed = 1;
    float yspeed = 1;

    m_rotation = m_rotation+delta.x()*xspeed;
    m_elevation = clamp(m_elevation+delta.y()*yspeed, -80, 80);

    updateDirection();
    event->accept();
}

void CameraControl::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
    event->accept();
}

void CameraControl::wheelEvent(QWheelEvent *event)
{
    QPoint numPixels = event->pixelDelta();
    if(numPixels.isNull() && (event->angleDelta().manhattanLength() % 8) > 0) {
        numPixels = event->angleDelta();
    }
    QPoint numDegrees = event->angleDelta() / 8;

    if (!numPixels.isNull()) {
        zoomWithPixels(numPixels);
    } else if (!numDegrees.isNull()) {
        QPoint numSteps = numDegrees / 15;
        zoomWithSteps(numSteps);
    }

    event->accept();
}


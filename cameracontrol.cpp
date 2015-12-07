#include <QtQuick>
#include "cameracontrol.h"
#include <iostream>

inline float clamp(float x, float a, float b)
{
    return x < a ? a : (x > b ? b : x);
}

CameraControl::CameraControl()
{
    forceActiveFocus();
    setAcceptedMouseButtons(Qt::LeftButton | Qt::MiddleButton);
    qDebug() << acceptedMouseButtons();
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

   if (event->buttons() & Qt::LeftButton) {
        float xspeed = 1;
        float yspeed = 1;

        m_rotation = m_rotation+delta.x()*xspeed;
        m_elevation = clamp(m_elevation+delta.y()*yspeed, -80, 80);

        updateDirection();
        event->accept();
    } else if ((event->buttons() & Qt::MidButton) || (event->buttons() & Qt::MiddleButton)) {
       m_posX = m_posX + delta.x()*0.01;
       m_posY = m_posY - delta.y()*0.01;
       m_position= QVector3D(m_posX, m_posY, 0.0f);
       positionChanged(m_position);
   }
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

void CameraControl::keyPressEvent(QKeyEvent *event)
{
   if (event->key() == Qt::Key_W) {
        m_posY += 0.05;
   } else if(event->key() == Qt::Key_S) {
       m_posY -= 0.05;
   } else if(event->key() == Qt::Key_D) {
       m_posX += 0.05;
   } else if (event->key() == Qt::Key_A) {
       m_posX -= 0.05;
   }
   m_position= QVector3D(m_posX, m_posY, 0.0f);
   positionChanged(m_position);
}

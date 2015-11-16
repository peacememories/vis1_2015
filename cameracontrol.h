#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include <QQuickItem>
#include "camera.h"

class CameraControl : public QQuickItem
{
    Q_OBJECT
public:
    CameraControl();
    Q_PROPERTY(Camera camera READ camera);
    Camera camera();
signals:

public slots:

private:
   Camera m_camera;

   // QQuickItem interface
protected:
   void mouseMoveEvent(QMouseEvent *event);

   // QQuickItem interface
protected:
   void mousePressEvent(QMouseEvent *event);
};

#endif // CAMERACONTROL_H

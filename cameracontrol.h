#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include <QQuickItem>

class CameraControl : public QQuickItem
{
    Q_OBJECT
public:
    CameraControl();
signals:

public slots:

private:
   // QQuickItem interface
protected:
   void mouseMoveEvent(QMouseEvent *event);

   // QQuickItem interface
protected:
   void mousePressEvent(QMouseEvent *event);
};

#endif // CAMERACONTROL_H

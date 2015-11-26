#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include <QQuickItem>
#include <QVector3D>


class CameraControl : public QQuickItem
{
    Q_OBJECT
public:
    Q_PROPERTY(QVector3D direction MEMBER m_direction NOTIFY directionChanged)

    CameraControl();
signals:
    void directionChanged(QVector3D const& direction);
private:
    QVector3D m_direction;

    float m_rotation;
    float m_elevation;
    float m_distance;

    QPoint m_lastPos;

    void updateDirection();
    void zoomWithPixels(QPoint dir);
    void zoomWithSteps(QPoint dir);

protected:
   void mouseMoveEvent(QMouseEvent *event);
   void mousePressEvent(QMouseEvent *event);
   void wheelEvent(QWheelEvent *event);
};

#endif // CAMERACONTROL_H

#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include <QQuickItem>
#include <QVector3D>


class CameraControl : public QQuickItem
{
    Q_OBJECT
public:
    Q_PROPERTY(QVector3D direction MEMBER m_direction NOTIFY directionChanged)
    Q_PROPERTY(QVector3D position MEMBER m_position NOTIFY positionChanged)

    CameraControl();
signals:
    void directionChanged(QVector3D const& direction);
    void positionChanged(QVector3D const& position);
private:
    QVector3D m_direction;
    QVector3D m_position;

    float m_rotation;
    float m_elevation;
    float m_distance;
    float m_posX;
    float m_posY;

    QPoint m_lastPos;

    void updateDirection();
    void zoomWithPixels(QPoint dir);
    void zoomWithSteps(QPoint dir);

protected:
   void mouseMoveEvent(QMouseEvent *event);
   void mousePressEvent(QMouseEvent *event);
   void wheelEvent(QWheelEvent *event);

   void keyPressEvent(QKeyEvent *event) override;
};

#endif // CAMERACONTROL_H

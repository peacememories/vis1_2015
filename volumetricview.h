#ifndef VOLUMETRICVIEW_H
#define VOLUMETRICVIEW_H

#include <QQuickFrameBufferObject>
#include <QProgressBar>
#include <QMatrix4x4>
#include <memory>
#include "Volume.h"
#include <QVector4D>

class VolumetricView : public QQuickFramebufferObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QVector3D viewDirection READ viewDirection WRITE setViewDirection)
    Q_PROPERTY(QVector3D viewPosition READ viewPosition WRITE setViewPosition)
    Q_PROPERTY(QVector4D color READ color WRITE setColor)
    Q_PROPERTY(bool useMIP READ useMIP WRITE setUseMIP)

    VolumetricView();
    Renderer *createRenderer() const;

    unsigned int volumeId() const;
    QVector3D viewDirection() const;
    void setViewDirection(const QVector3D dir);
    QVector3D viewPosition() const;
    void setViewPosition(const QVector3D pos);
    QVector4D color() const;
    bool useMIP() const;
    Q_INVOKABLE void setRed(float colR);
    Q_INVOKABLE void setGreen(float colG);
    Q_INVOKABLE void setBlue(float colB);
    Q_INVOKABLE void setUseMIP(bool MIP);
    QSharedPointer<const Volume> volume() const;
public slots:
    void loadFile(QUrl);
signals:
    void progressValueChanged(int);
private:
     void setColor(QVector4D col);
    QProgressBar m_progress;
    QSharedPointer<const Volume> m_volume;
    unsigned int m_volumeId;
    QVector3D m_viewDirection;
    QVector3D m_viewPosition;
    QVector4D m_color;
    bool m_useMIP;
private slots:
};

#endif // VOLUMETRICVIEW_H

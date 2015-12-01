#ifndef VOLUMETRICVIEW_H
#define VOLUMETRICVIEW_H

#include <QQuickFrameBufferObject>
#include <QProgressBar>
#include <QMatrix4x4>
#include <memory>
#include "Volume.h"

class VolumetricView : public QQuickFramebufferObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QVector3D viewDirection READ viewDirection WRITE setViewDirection)
    Q_PROPERTY(QVector3D viewPosition READ viewPosition WRITE setViewPosition)

    VolumetricView();
    Renderer *createRenderer() const;

    unsigned int volumeId() const;
    QVector3D viewDirection() const;
    void setViewDirection(const QVector3D dir);
    QVector3D viewPosition() const;
    void setViewPosition(const QVector3D pos);
    QSharedPointer<const Volume> volume() const;
public slots:
    void loadFile(QUrl);
signals:
    void progressValueChanged(int);
private:
    QProgressBar m_progress;
    QSharedPointer<const Volume> m_volume;
    unsigned int m_volumeId;
    QVector3D m_viewDirection;
    QVector3D m_viewPosition;
private slots:
};

#endif // VOLUMETRICVIEW_H

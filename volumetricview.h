#ifndef VOLUMETRICVIEW_H
#define VOLUMETRICVIEW_H

#include <QQuickFrameBufferObject>
#include <QProgressBar>
#include <QMatrix4x4>
#include <memory>
#include "Volume.h"
#include "camera.h"

class VolumetricView : public QQuickFramebufferObject
{
    Q_OBJECT

    Q_PROPERTY(Camera* camera MEMBER m_camera)
public:
    VolumetricView();
    Renderer *createRenderer() const;
    unsigned int volumeId();
    QMatrix4x4 vp();
public slots:
    void loadFile(QUrl);
signals:
    void progressValueChanged(int);
private:
    QProgressBar m_progress;
    std::unique_ptr<Volume> m_volume;
    unsigned int m_volumeId;
    Camera* m_camera;

private slots:
};

#endif // VOLUMETRICVIEW_H

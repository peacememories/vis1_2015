#ifndef VOLUMETRICVIEW_H
#define VOLUMETRICVIEW_H

#include <QQuickFrameBufferObject>
#include <QProgressBar>
#include <memory>
#include "Volume.h"

class VolumetricView : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    VolumetricView();
    Renderer *createRenderer() const;
    unsigned int volumeId();
public slots:
    void loadFile(QUrl);
signals:
    void progressValueChanged(int);
private:
    QProgressBar m_progress;
    std::unique_ptr<Volume> m_volume;
    unsigned int m_volumeId;

private slots:
};

#endif // VOLUMETRICVIEW_H

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
public slots:
    void loadFile(QUrl);
signals:
    void progressValueChanged(int);
private:
    QProgressBar m_progress;
    std::unique_ptr<Volume> m_volume;

private slots:
};

#endif // VOLUMETRICVIEW_H

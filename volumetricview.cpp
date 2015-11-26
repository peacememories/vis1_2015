#include "volumetricrenderer.h"
#include "volumetricview.h"

VolumetricView::VolumetricView()
{
    m_viewDirection = QVector3D(0,3,3);
}

QQuickFramebufferObject::Renderer *VolumetricView::createRenderer() const
{
    return new VolumetricRenderer;
}

unsigned int VolumetricView::volumeId()
{
    return m_volumeId;
}

QVector3D VolumetricView::viewDirection()
{
    return m_viewDirection;
}

void VolumetricView::setViewDirection(QVector3D dir)
{
    m_viewDirection = dir;
    update();
}

void VolumetricView::loadFile(QUrl url)
{
    std::unique_ptr<Volume> newVolume(new Volume);
    newVolume->loadFromFile(url.toLocalFile(), &m_progress);
    m_volume = std::move(newVolume);
    m_volumeId = qrand();
    update();
}


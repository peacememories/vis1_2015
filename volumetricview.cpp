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

unsigned int VolumetricView::volumeId() const
{
    return m_volumeId;
}

QVector3D VolumetricView::viewDirection() const
{
    return m_viewDirection;
}

void VolumetricView::setViewDirection(const QVector3D dir)
{
    m_viewDirection = dir;
    update();
}

QSharedPointer<const Volume> VolumetricView::volume() const
{
    return m_volume;
}

void VolumetricView::loadFile(QUrl url)
{
    QSharedPointer<Volume> newVolume(new Volume);
    newVolume->loadFromFile(url.toLocalFile(), &m_progress);
    m_volume = newVolume;
    m_volumeId = qrand();
    update();
}


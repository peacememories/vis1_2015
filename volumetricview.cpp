#include "volumetricrenderer.h"
#include "volumetricview.h"

VolumetricView::VolumetricView()
{
    m_viewDirection = QVector3D(0,3,3);
    m_viewPosition = QVector3D(0, 0, 0);
    m_color = QVector4D(1.0, 0.0, 1.0, 1.0);
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

QVector3D VolumetricView::viewPosition() const
{
    return m_viewPosition;
}
void VolumetricView::setViewPosition(const QVector3D pos)
{
    m_viewPosition = pos;
    update();
}

QVector4D VolumetricView::color() const
{
    return m_color;
}

void VolumetricView::setColor(QVector4D col)
{
    m_color = col;
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


#include "volumetricrenderer.h"
#include "volumetricview.h"

VolumetricView::VolumetricView()
{
}

QQuickFramebufferObject::Renderer *VolumetricView::createRenderer() const
{
    return new VolumetricRenderer;
}

unsigned int VolumetricView::volumeId()
{
    return m_volumeId;
}

QMatrix4x4 VolumetricView::vp()
{
    return m_camera->view() * m_camera->projection();
}

void VolumetricView::loadFile(QUrl url)
{
    std::unique_ptr<Volume> newVolume(new Volume);
    newVolume->loadFromFile(url.toLocalFile(), &m_progress);
    m_volume = std::move(newVolume);
    m_volumeId = qrand();
}


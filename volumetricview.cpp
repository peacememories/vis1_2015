#include "volumetricrenderer.h"
#include "volumetricview.h"

VolumetricView::VolumetricView()
{
}

QQuickFramebufferObject::Renderer *VolumetricView::createRenderer() const
{
    return new VolumetricRenderer;
}

void VolumetricView::loadFile(QString url)
{
    std::unique_ptr<Volume> newVolume(new Volume);
    newVolume->loadFromFile(url, &m_progress);
    m_volume = std::move(newVolume);
}


#include "volumetricrenderer.h"
#include "volumetricview.h"

VolumetricView::VolumetricView()
{
}

QQuickFramebufferObject::Renderer *VolumetricView::createRenderer() const
{
    return new VolumetricRenderer;
}

void VolumetricView::loadFile(QUrl url)
{
    std::unique_ptr<Volume> newVolume(new Volume);
    newVolume->loadFromFile(url.toLocalFile(), &m_progress);
    m_volume = std::move(newVolume);
}


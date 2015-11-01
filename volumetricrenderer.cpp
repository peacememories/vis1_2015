#include "volumetricrenderer.h"

#include <QOpenGLFramebufferObject>
#include "volumetricview.h"

VolumetricRenderer::VolumetricRenderer()
{
    initializeOpenGLFunctions();
}

void VolumetricRenderer::render()
{

}

QOpenGLFramebufferObject *VolumetricRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::Depth);
    return new QOpenGLFramebufferObject(size, format);
}

void VolumetricRenderer::synchronize(QQuickFramebufferObject * input)
{
    VolumetricView* view = qobject_cast<VolumetricView*>(input);

}


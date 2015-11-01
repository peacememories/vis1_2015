#ifndef VOLUMETRICRENDERER_H
#define VOLUMETRICRENDERER_H

#include <QQuickFrameBufferObject>
#include <QOpenGLFunctions_2_0>

class VolumetricRenderer : public QQuickFramebufferObject::Renderer, QOpenGLFunctions_2_0
{
public:
    VolumetricRenderer();

    // Renderer interface
protected:
    void render();
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size);
    void synchronize(QQuickFramebufferObject *);
};

#endif // VOLUMETRICRENDERER_H

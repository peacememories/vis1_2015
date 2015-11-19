#ifndef VOLUMETRICRENDERER_H
#define VOLUMETRICRENDERER_H

#include <QQuickFrameBufferObject>
#include <QOpenGLFunctions_3_3_Compatibility>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QQuickWindow>
#include <QOpenGLDebugLogger>

#include "openglloghandler.h"

class VolumetricRenderer : public QQuickFramebufferObject::Renderer, QOpenGLFunctions_3_3_Compatibility
{
public:
    VolumetricRenderer();

    // Renderer interface
protected:
    void render();
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size);
    void synchronize(QQuickFramebufferObject *);
private:
    unsigned int m_volumeId;
    QQuickWindow* m_window;
    QMatrix4x4 m_mvp;
    QOpenGLBuffer m_cubeVertices = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer m_cubeIndices = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    QOpenGLShaderProgram m_cubeprogram;

    QOpenGLDebugLogger m_logger;
    OpenGLLogHandler m_logHandler;

    void initProgram();
    void initCube();
    void initProjection();
};

#endif // VOLUMETRICRENDERER_H

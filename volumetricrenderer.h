#ifndef VOLUMETRICRENDERER_H
#define VOLUMETRICRENDERER_H

#include <QQuickFrameBufferObject>
#include <QOpenGLFunctions_4_3_Compatibility>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QQuickWindow>
#include <QOpenGLDebugLogger>
#include <QOpenGLTexture>

#include "openglloghandler.h"
#include "geometry.h"

class VolumetricRenderer : public QQuickFramebufferObject::Renderer, QOpenGLFunctions_4_3_Compatibility
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


    QOpenGLDebugLogger m_logger;
    OpenGLLogHandler m_logHandler;

    Mesh m_mesh;
    QOpenGLBuffer m_vertexBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer m_normalBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer m_indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    QOpenGLVertexArrayObject m_vao;
    QOpenGLShaderProgram m_program;

    QMatrix4x4 m_vp;

    QSharedPointer<QOpenGLTexture> m_voxels;
};

#endif // VOLUMETRICRENDERER_H

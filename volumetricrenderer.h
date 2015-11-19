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

#include "openglloghandler.h"

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

    QVector<QVector3D> m_vertices;
    QVector<QVector3D> m_normals;
    QOpenGLBuffer m_vertexBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer m_normalBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLShaderProgram m_program;
};

#endif // VOLUMETRICRENDERER_H

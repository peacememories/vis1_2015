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
    QVector<GLuint> m_indices;
    QOpenGLBuffer m_vertexBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer m_normalBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer m_indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    QOpenGLVertexArrayObject m_vao;
    QOpenGLShaderProgram m_program;

    QMatrix4x4 m_vp;

    float m_aspectRatio;
};

#endif // VOLUMETRICRENDERER_H

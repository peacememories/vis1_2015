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
#include <memory>
#include <QVector4D>

#include "openglloghandler.h"
#include "geometry.h"
#include "glmesh.h"

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
    GLMesh m_glMesh;
    QOpenGLShaderProgram m_bfProgram;
    QOpenGLShaderProgram m_sampleProgram;
    QOpenGLShaderProgram m_alphaProgram;


    std::unique_ptr<QOpenGLFramebufferObject> m_backfaceBuffer;

    QMatrix4x4 m_vp;
    QVector4D m_color;
    bool m_useMIP = true;

    QSharedPointer<QOpenGLTexture> m_voxels;
};

#endif // VOLUMETRICRENDERER_H

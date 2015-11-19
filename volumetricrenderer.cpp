#include "volumetricrenderer.h"

#include <QOpenGLFramebufferObject>
#include <QOpenGLShader>
#include <QVector2D>
#include <QQuickWindow>
#include <QOpenGLDebugLogger>
#include <QSurfaceFormat>
#include "volumetricview.h"
#include "openglloghandler.h"

VolumetricRenderer::VolumetricRenderer()
{
    initializeOpenGLFunctions();
    m_logger.initialize();
    m_logger.connect(&m_logger, SIGNAL(messageLogged(QOpenGLDebugMessage)), &m_logHandler, SLOT(handleLoggedMessage(QOpenGLDebugMessage)));
    m_logger.startLogging();

    //renderer.initialize();

    m_vertices << QVector3D(1, 1, 0);
    m_vertices << QVector3D(0, -1, 0);
    m_vertices << QVector3D(-1, 1, 0);

    m_normals << QVector3D(0,0,-1);
    m_normals << QVector3D(0,0,-1);
    m_normals << QVector3D(0,0,-1);

    m_vertexBuffer.create();
    m_vertexBuffer.bind();
    m_vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexBuffer.allocate(m_vertices.constData(), m_vertices.size()*sizeof(QVector3D));
    m_vertexBuffer.release();

    m_normalBuffer.create();
    m_normalBuffer.bind();
    m_normalBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_normalBuffer.allocate(m_normals.constData(), m_normals.size()*sizeof(QVector3D));
    m_normalBuffer.release();

    m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/cube.vsh");
    m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/cube.fsh");
    m_program.link();
}

void VolumetricRenderer::render()
{
    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);


    m_program.bind();
    m_program.enableAttributeArray(0);
    m_program.enableAttributeArray(1);
    m_program.setAttributeArray(0, m_vertices.constData());
    m_vertexBuffer.bind();
    m_program.setAttributeBuffer(0, GL_FLOAT, 0, 3);
    m_normalBuffer.bind();
    m_program.setAttributeBuffer(1, GL_FLOAT, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    m_program.disableAttributeArray(0);
    m_program.disableAttributeArray(1);
    m_program.release();

    update();
    m_window->resetOpenGLState();
}

QOpenGLFramebufferObject *VolumetricRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}

void VolumetricRenderer::synchronize(QQuickFramebufferObject * input)
{
    VolumetricView* view = qobject_cast<VolumetricView*>(input);
    m_window = view->window();
    //Reload voxel data
    if(view->volumeId() != m_volumeId) {

    }
}


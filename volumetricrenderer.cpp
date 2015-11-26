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

    cube(m_mesh);

    m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/cube.vsh");
    m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/cube.fsh");
    m_program.link();

    m_vao.create();
    m_vao.bind();
    m_program.bind();

    m_vertexBuffer.create();
    m_vertexBuffer.bind();
    m_vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexBuffer.allocate(m_mesh.vertices.constData(), m_mesh.vertices.size()*sizeof(QVector3D));

    m_program.enableAttributeArray(0);
    m_program.setAttributeBuffer(0, GL_FLOAT, 0, 3);
    m_vertexBuffer.release();

    m_normalBuffer.create();
    m_normalBuffer.bind();
    m_normalBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_normalBuffer.allocate(m_mesh.normals.constData(), m_mesh.normals.size()*sizeof(QVector3D));

    m_program.enableAttributeArray(1);
    m_program.setAttributeBuffer(1, GL_FLOAT, 0, 3);
    m_normalBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indexBuffer.allocate(m_mesh.indices.constData(), m_mesh.indices.size()*sizeof(GLuint));

    m_program.release();
    m_vao.release();
}

void VolumetricRenderer::render()
{
    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    m_program.bind();

    m_program.setUniformValue("mvp", m_vp);
    m_vao.bind();

    glDrawElements(GL_TRIANGLES, m_mesh.indices.size(), GL_UNSIGNED_INT, 0);

    m_vao.release();

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

    float aspectRatio = view->width()/view->height();

    m_vp.setToIdentity();
    m_vp.scale(1,-1,1);
    m_vp.perspective(65, aspectRatio, 0.1, 100);
    m_vp.lookAt(view->viewDirection(), QVector3D(0,0,0), QVector3D(0,1,0));

    //Reload voxel data
    if(view->volumeId() != m_volumeId) {
        m_volumeId = view->volumeId();
    }
}


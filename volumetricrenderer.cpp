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
    m_glMesh.create();
    m_glMesh.loadMesh(m_mesh);

    m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/cube.vsh");
    m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/cube.fsh");
    m_program.link();
}

void VolumetricRenderer::render()
{
    glDepthMask(true);

    glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!m_voxels.isNull()) {
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        m_program.bind();

        m_voxels->bind(0);

        QMatrix4x4 modelMatrix;
        modelMatrix.scale(m_voxels->width(), m_voxels->height(), m_voxels->depth());
        modelMatrix.scale(0.01);

        m_program.setUniformValue("mvp", m_vp*modelMatrix);
        m_program.setUniformValue("nm", modelMatrix.normalMatrix());

        m_glMesh.bind();

        glDrawElements(GL_TRIANGLES, m_glMesh.size(), GL_UNSIGNED_INT, 0);

        m_glMesh.release();

        m_program.release();
    }
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
    if(view->volumeId() != m_volumeId && !view->volume().isNull()) {
        m_volumeId = view->volumeId();
        QSharedPointer<const Volume> volume = view->volume();
        m_voxels = QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(QOpenGLTexture::Target3D));
        m_voxels->create();
        m_voxels->setSize(volume->width(), volume->height(), volume->depth());
        m_voxels->setData(QOpenGLTexture::Red, QOpenGLTexture::Float32, volume->voxels());
    }
}


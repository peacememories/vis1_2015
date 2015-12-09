#include "volumetricrenderer.h"

#include <QOpenGLFramebufferObject>
#include <QOpenGLShader>
#include <QVector2D>
#include <QQuickWindow>
#include <QOpenGLDebugLogger>
#include <QSurfaceFormat>
#include <QOpenGLPixelTransferOptions>
#include "volumetricview.h"
#include "openglloghandler.h"
#include <iostream>

VolumetricRenderer::VolumetricRenderer()
{
    initializeOpenGLFunctions();
    m_logger.initialize();
    m_logger.connect(&m_logger, SIGNAL(messageLogged(QOpenGLDebugMessage)), &m_logHandler, SLOT(handleLoggedMessage(QOpenGLDebugMessage)));
    m_logger.startLogging();

    cube(m_mesh);
    m_glMesh.create();
    m_glMesh.loadMesh(m_mesh);

    m_bfProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/cube.vsh");
    m_bfProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/cube.fsh");
    m_bfProgram.link();

    m_sampleProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/mip.vsh");
    m_sampleProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/mip.fsh");
    m_sampleProgram.link();

    m_alphaProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/alpha.vsh");
    m_alphaProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/alpha.fsh");
    m_alphaProgram.link();
}

void VolumetricRenderer::render()
{
    glDepthMask(true);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CCW);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!m_voxels.isNull()) {
        QMatrix4x4 modelMatrix;
        modelMatrix.scale(m_voxels->width(), m_voxels->height(), m_voxels->depth());
        modelMatrix.scale(-0.01);
        modelMatrix.rotate(180.0, QVector3D(0,1,0));

        m_bfProgram.bind();
        m_bfProgram.setUniformValue("mvp", m_vp*modelMatrix);
        m_bfProgram.setUniformValue("mm", modelMatrix);
        m_bfProgram.setUniformValue("voxels", 0);
        m_voxels->bind(0);
        m_glMesh.bind();


        m_backfaceBuffer->bind();
        glCullFace(GL_FRONT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, m_glMesh.size(), GL_UNSIGNED_INT, 0);
        m_backfaceBuffer->release();

        if (m_useMIP) {
            m_sampleProgram.bind();
            m_sampleProgram.setUniformValue("mvp", m_vp*modelMatrix);
            m_sampleProgram.setUniformValue("mm", modelMatrix);
            m_sampleProgram.setUniformValue("windowSize", framebufferObject()->size());
            m_sampleProgram.setUniformValue("voxels", 0);
            m_sampleProgram.setUniformValue("backfaces", 1);
            m_sampleProgram.setUniformValue("myColor", QVector3D(m_color.x(), m_color.y(), m_color.z()));
        } else {
            m_alphaProgram.bind();
            m_alphaProgram.setUniformValue("mvp", m_vp*modelMatrix);
            m_alphaProgram.setUniformValue("mm", modelMatrix);
            m_alphaProgram.setUniformValue("windowSize", framebufferObject()->size());
            m_alphaProgram.setUniformValue("voxels", 0);
            m_alphaProgram.setUniformValue("backfaces", 1);
            m_alphaProgram.setUniformValue("myColor", QVector3D(m_color.x(), m_color.y(), m_color.z()));
        }
        m_voxels->bind(0);

        framebufferObject()->bind();
        glActiveTexture(GL_TEXTURE1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_backfaceBuffer->texture());
        glCullFace(GL_BACK);
        glDrawElements(GL_TRIANGLES, m_glMesh.size(), GL_UNSIGNED_INT, 0);

        m_glMesh.release();
        if (m_useMIP) {
            m_sampleProgram.release();
        } else {
            m_alphaProgram.release();
        }

    }
    update();
    m_window->resetOpenGLState();
}

QOpenGLFramebufferObject *VolumetricRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat textureFormat;
    textureFormat.setAttachment(QOpenGLFramebufferObject::Depth);
    textureFormat.setInternalTextureFormat(GL_RGBA32F);
    m_backfaceBuffer.reset(new QOpenGLFramebufferObject(size, textureFormat));
    QOpenGLFramebufferObjectFormat mainBufferFormat;
    mainBufferFormat.setAttachment(QOpenGLFramebufferObject::Depth);
    mainBufferFormat.setSamples(0);
    return new QOpenGLFramebufferObject(size, mainBufferFormat);
}

void VolumetricRenderer::synchronize(QQuickFramebufferObject * input)
{
    VolumetricView* view = qobject_cast<VolumetricView*>(input);
    m_window = view->window();

    float aspectRatio = view->width()/view->height();

    m_vp.setToIdentity();
    m_vp.scale(1,-1,1);
    m_vp.perspective(65, aspectRatio, 0.1, 100);
    m_vp.translate(view->viewPosition().x(), view->viewPosition().y(), 0.0);
    m_vp.lookAt(view->viewDirection() ,  QVector3D(0,0,0), QVector3D(0,1,0));

    //Reload voxel data
    if(view->volumeId() != m_volumeId && !view->volume().isNull()) {
        m_volumeId = view->volumeId();
        QSharedPointer<const Volume> volume = view->volume();
        m_voxels = QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(QOpenGLTexture::Target3D));
        m_voxels->create();
        m_voxels->bind();
        m_voxels->setSize(volume->width(), volume->height(), volume->depth());
        m_voxels->setFormat(QOpenGLTexture::R32F);
        m_voxels->setMinificationFilter(QOpenGLTexture::LinearMipMapNearest);
        m_voxels->setMagnificationFilter(QOpenGLTexture::LinearMipMapNearest);
        m_voxels->allocateStorage(QOpenGLTexture::Red, QOpenGLTexture::Float32);

        QOpenGLPixelTransferOptions transfer;
        transfer.setRowLength(volume->width());
        transfer.setImageHeight(volume->height());
        transfer.setAlignment(1);
        m_voxels->setData(QOpenGLTexture::Red, QOpenGLTexture::Float32, volume->voxels(), &transfer);
        m_voxels->release();
    }

    m_color = view->color();
    m_useMIP = view->useMIP();
}


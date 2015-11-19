#include "volumetricrenderer.h"

#include <QOpenGLFramebufferObject>
#include <QOpenGLShader>
#include <QVector2D>
#include <QQuickWindow>
#include <QOpenGLDebugLogger>
#include <QSurfaceFormat>
#include "volumetricview.h"
#include "openglloghandler.h"


struct VertexData {
    QVector3D position;
    QVector2D texCoord;
};

VolumetricRenderer::VolumetricRenderer()
{
    initializeOpenGLFunctions();
    m_logger.initialize();
    m_logger.connect(&m_logger, SIGNAL(messageLogged(QOpenGLDebugMessage)), &m_logHandler, SLOT(handleLoggedMessage(QOpenGLDebugMessage)));
    m_logger.startLogging();
    initProjection();
    initProgram();
    initCube();
}

void VolumetricRenderer::render()
{
    glClearColor(0,0,1,1);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    m_cubeprogram.bind();
    m_cubeprogram.setUniformValue("mvp", m_mvp);
    m_cubeVertices.bind();
    m_cubeIndices.bind();

    m_cubeprogram.enableAttributeArray("position");
    m_cubeprogram.setAttributeBuffer("position", GL_FLOAT, 0, 3, sizeof(VertexData));

    m_cubeprogram.enableAttributeArray("uv_coord");
    m_cubeprogram.setAttributeBuffer("uv_coord", GL_FLOAT, sizeof(QVector3D), 2, sizeof(VertexData));

    glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_SHORT, 0);
    GetLastError();

    m_cubeVertices.release();
    m_cubeIndices.release();
    m_cubeprogram.release();

    glDisable(GL_DEPTH_TEST);
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

void VolumetricRenderer::initProgram()
{
    m_cubeprogram.create();

    if(!m_cubeprogram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/cube.vsh")) {
        qDebug() << m_cubeprogram.log();
    }
    if(!m_cubeprogram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/cube.fsh")) {
        qDebug() << m_cubeprogram.log();
    }

    m_cubeprogram.bindAttributeLocation("position", 0);
    m_cubeprogram.bindAttributeLocation("uv_coord", 1);

    if(!m_cubeprogram.link()) {
        qDebug() << m_cubeprogram.log();
    }
}

void VolumetricRenderer::initCube()
{
    // For cube we would need only 8 vertices but we have to
        // duplicate vertex for each face because texture coordinate
        // is different.
        VertexData vertices[] = {
            // Vertex data for face 0
            {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
            {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
            {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
            {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

            // Vertex data for face 1
            {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
            {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
            {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
            {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

            // Vertex data for face 2
            {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
            {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
            {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
            {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

            // Vertex data for face 3
            {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
            {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
            {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
            {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

            // Vertex data for face 4
            {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
            {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
            {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
            {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

            // Vertex data for face 5
            {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
            {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
            {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
            {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
        };

        // Indices for drawing cube faces using triangle strips.
        // Triangle strips can be connected by duplicating indices
        // between the strips. If connecting strips have opposite
        // vertex order then last index of the first strip and first
        // index of the second strip needs to be duplicated. If
        // connecting strips have same vertex order then only last
        // index of the first strip needs to be duplicated.
        GLushort indices[] = {
             0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
             4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
             8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
            12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
            16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
            20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
        };

        m_cubeVertices.create();
        m_cubeVertices.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_cubeIndices.create();
        m_cubeIndices.setUsagePattern(QOpenGLBuffer::StaticDraw);
        // Transfer vertex data to VBO 0
        m_cubeVertices.bind();
        m_cubeVertices.allocate(vertices, 24 * sizeof(VertexData));
        m_cubeVertices.release();

        // Transfer index data to VBO 1
        m_cubeIndices.bind();
        m_cubeIndices.allocate(indices, 34 * sizeof(GLushort));
        m_cubeIndices.release();
}

void VolumetricRenderer::initProjection()
{
    QMatrix4x4 projection;
    projection.setToIdentity();
    projection.perspective(70, 1.333, 0.1, 1000);
    QMatrix4x4 view;
    view.setToIdentity();
    view.lookAt(QVector3D(3,1,3), QVector3D(0,0,0), QVector3D(0,1,0));
    m_mvp = view*projection;
}


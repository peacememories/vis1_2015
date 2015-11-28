#ifndef GLMESH_H
#define GLMESH_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "geometry.h"

class GLMesh : private QOpenGLFunctions
{
public:
    GLMesh();
    bool create();

    void bind();
    void release();

    bool loadMesh(const Mesh& mesh);

    unsigned int size() const;
private:
    QOpenGLBuffer m_vertices = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer m_normals = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer m_indices = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    QOpenGLVertexArrayObject m_vao;
    unsigned int m_indexSize;
};

#endif // GLMESH_H

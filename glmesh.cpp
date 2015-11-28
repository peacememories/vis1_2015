#include "glmesh.h"

#include<QVector3D>

GLMesh::GLMesh()
{

}

void GLMesh::bind()
{
    m_vao.bind();
}

void GLMesh::release()
{
    m_vao.release();
}

bool GLMesh::loadMesh(const Mesh& mesh)
{
    m_vertices.bind();
    m_vertices.allocate(mesh.vertices.constData(), mesh.vertices.size()*sizeof(QVector3D));
    m_normals.bind();
    m_normals.allocate(mesh.normals.constData(), mesh.normals.size()*sizeof(QVector3D));
    m_indices.bind();
    m_indices.allocate(mesh.indices.constData(), mesh.indices.size()*sizeof(unsigned int));
    m_indices.release();

    m_indexSize = mesh.indices.size();

    return true;
}

unsigned int GLMesh::size() const
{
    return m_indexSize;
}

bool GLMesh::create()
{
    initializeOpenGLFunctions();
    if(!m_vertices.create()) {
        return false;
    }
    if(!m_normals.create()) {
        return false;
    }
    if(!m_indices.create()) {
        return false;
    }
    if(!m_vao.create()) {
        return false;
    }

    m_vao.bind();

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    m_vertices.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    m_vertices.release();

    m_vertices.bind();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, 0);
    m_vertices.release();

    m_indices.bind();

    m_vao.release();

    return true;
}


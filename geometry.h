#ifndef GEOMETRY_H
#define GEOMETRY_H

#include<QVector>
#include<QVector3D>
#include<QVector2D>

struct Mesh {
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<unsigned int> indices;
};

void plane(Mesh&, QVector3D const& direction = QVector3D(0,0,1), QVector3D const& position = QVector3D(0,0,0), QVector2D const& size = QVector2D(1,1));

void cube(Mesh&, QVector3D const& position = QVector3D(0,0,0), QVector3D const& size = QVector3D(1,1,1));

#endif // GEOMETRY_H


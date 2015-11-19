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

void plane(Mesh&, QVector3D direction = QVector3D(0,0,1), QVector3D position = QVector3D(0,0,0), QVector2D size = QVector2D(1,1));

void cube(Mesh&, QVector3D position, QVector3D size);

#endif // GEOMETRY_H


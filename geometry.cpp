#include "geometry.h"

#include <QMatrix4x4>



void plane(Mesh &mesh, QVector3D direction, QVector3D position, QVector2D size)
{
    unsigned int index = mesh.vertices.size();
    QMatrix4x4 mapper;
    mapper.scale(size.x(), size.y());
    mapper.rotate(QQuaternion::fromDirection(direction, QVector3D(0,1,0)));
    mapper.translate(position);

    mesh.vertices << mapper*QVector3D(-1,-1,0);
    mesh.vertices << mapper*QVector3D(-1,1,0);
    mesh.vertices << mapper*QVector3D(1,1,0);
    mesh.vertices << mapper*QVector3D(1,-1,0);

    for(int i = 0; i < 4; i++) {
        mesh.normals << direction;
    }

    mesh.indices << index + 0;
    mesh.indices << index + 1;
    mesh.indices << index + 2;
    mesh.indices << index + 0;
    mesh.indices << index + 2;
    mesh.indices << index + 3;
}

void cube(Mesh &mesh, QVector3D position, QVector3D size)
{
}

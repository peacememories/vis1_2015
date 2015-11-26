#include "geometry.h"

#include <QMatrix4x4>



void plane(Mesh &mesh, const QVector3D &direction, const QVector3D &position, const QVector2D &size)
{
    unsigned int index = mesh.vertices.size();
    QMatrix4x4 mapper;

    mapper.translate(position);

    QVector3D up(0,1,0);
    if(direction.y() == 1) {
        up = QVector3D(0,0,1);
    }

    mapper.rotate(QQuaternion::fromDirection(direction, up));

    mapper.scale(size.x(), size.y());

    mesh.vertices << mapper*QVector3D(-0.5,-0.5,0);
    mesh.vertices << mapper*QVector3D(0.5,-0.5,0);
    mesh.vertices << mapper*QVector3D(-0.5,0.5,0);
    mesh.vertices << mapper*QVector3D(0.5,0.5,0);

    for(int i = 0; i < 4; i++) {
        mesh.normals << direction;
    }

    mesh.indices << index + 0;
    mesh.indices << index + 1;
    mesh.indices << index + 2;
    mesh.indices << index + 2;
    mesh.indices << index + 1;
    mesh.indices << index + 3;
}

void cube(Mesh &mesh, QVector3D const& position, QVector3D const& size)
{
    plane(mesh, QVector3D(0,0,-1), position+QVector3D(0,0,-0.5), QVector2D(size.x(), size.y()));
    plane(mesh, QVector3D(0,0,1), position+QVector3D(0,0,0.5), QVector2D(size.x(), size.y()));

    plane(mesh, QVector3D(0,1,0), position+QVector3D(0,0.5,0), QVector2D(size.x(), size.z()));
    plane(mesh, QVector3D(0,-1,0), position+QVector3D(0,-0.5,0), QVector2D(size.x(), size.z()));

    plane(mesh, QVector3D(1,0,0), position+QVector3D(0.5,0,0), QVector2D(size.z(), size.y()));
    plane(mesh, QVector3D(-1,0,0), position+QVector3D(-0.5,0,0), QVector2D(size.z(), size.y()));
}

#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>

class Camera
{
public:
    explicit Camera();
    Camera(Camera& other);
    virtual ~Camera();
    QMatrix4x4 model();
    QMatrix4x4 view();
    QMatrix4x4 projection();
};

#endif // CAMERA_H

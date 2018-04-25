#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QVector3D>
#include <QMatrix4x4>

#include <QtMath>

namespace CameraConstants {

const float CENTERX_MIN = -10000.0;
const float CENTERX_MAX =  10000.0;
const float CENTERY_MIN = -10000.0;
const float CENTERY_MAX =  10000.0;
const float CENTERZ_MIN = -10000.0;
const float CENTERZ_MAX =  10000.0;
const float YAW_MIN     =      0.0;
const float YAW_MAX     =    360.0;
const float PITCH_MIN   =    -89.9;
const float PITCH_MAX   =     89.9;
const float RADIUS_MIN  =      1.0;
const float RADIUS_MAX  =    100.0;

} // CameraConstants

class Camera
{
public:
    Camera();

    void moveCenter(const QVector3D &center);   
    void rotateYaw(float dangle);
    void rotatePitch(float dangle);
    void rotate(float dyawAngle, float dpitchAngle);
    void zoom(float factor);

    QMatrix4x4 getViewMatrix() const;

private:
    float m_radius;
    float m_yaw;
    float m_pitch;

    QVector3D m_eye;
    QVector3D m_center;
    QVector3D m_up;

    void updateEye();

    void normilizeYaw();
    void normilizePitch();
    void normilizeRadius();
};

#endif // CAMERA_HPP

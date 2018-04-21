#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QVector3D>
#include <QMatrix4x4>

#include <QtMath>

class Camera
{
public:
    Camera();

    void moveCenter(const QVector3D &center);   
    void rotateYaw(float dangle);
    void rotatePitch(float dangle);
    void rotate(float dyawAngle, float dyawPitch);
    void zoomUp();   //zoom-
    void zoomDown(); //zoom+

    QMatrix4x4 getViewMatrix() const;

private:
    constexpr static const float YAW_MIN    =    0.0;
    constexpr static const float YAW_MAX    =  360.0;
    constexpr static const float PITCH_MIN  =  -89.9;
    constexpr static const float PITCH_MAX  =   89.9;
    constexpr static const float RADIUS_MIN =    1.0;
    constexpr static const float RADIUS_MAX =  100.0;
    constexpr static const float KZOOM      =    0.9;

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

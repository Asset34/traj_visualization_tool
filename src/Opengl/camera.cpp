#include "camera.hpp"

Camera::Camera()
    : m_radius(7.0),
      m_yaw(0.0),
      m_pitch(0.0),
      m_eye(QVector3D(0.0, 0.0, m_radius)),
      m_center(QVector3D(0.0, 0.0, 0.0)),
      m_up(QVector3D(0.0, 1.0, 0.0))
{
}

void Camera::moveCenter(const QVector3D &center)
{
    m_center = center;
}

void Camera::rotateYaw(float dangle)
{
    m_yaw += dangle;
    normilizeAngle(m_yaw);

    updateEye();
}

void Camera::rotatePitch(float dangle)
{
    m_pitch += dangle;
    normilizeAngle(m_pitch);

    updateEye();
}

void Camera::rotate(float dyawAngle, float dyawPitch)
{
    rotateYaw(dyawAngle);
    rotatePitch(dyawPitch);
}

void Camera::zoomUp()
{
    m_radius /= KZOOM;

    updateEye();
}

void Camera::zoomDown()
{
    m_radius *= KZOOM;

    updateEye();
}

QMatrix4x4 Camera::getViewMatrix() const
{
    QMatrix4x4 view;
    view.lookAt(m_eye, m_center, m_up);

    return view;
}

void Camera::updateEye()
{
    m_eye.setX(m_radius * qCos(qDegreesToRadians(m_pitch)) * qSin(qDegreesToRadians(m_yaw)));
    m_eye.setY(m_radius * qSin(qDegreesToRadians(m_pitch)));
    m_eye.setZ(m_radius * qCos(qDegreesToRadians(m_pitch)) * qCos(qDegreesToRadians(m_yaw)));
}

void Camera::normilizeAngle(float &angle)
{
    if (angle < ANGLE_MIN) {
        angle = ANGLE_MAX;
    }
    else if (angle > ANGLE_MAX) {
        angle = ANGLE_MIN;
    }
}

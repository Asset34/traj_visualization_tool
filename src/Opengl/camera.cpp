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
    normilizeYaw();

    updateEye();
}

void Camera::rotatePitch(float dangle)
{
    m_pitch += dangle;
    normilizePitch();

    updateEye();
}

void Camera::rotate(float dyawAngle, float dpitchAngle)
{
    rotateYaw(dyawAngle);
    rotatePitch(dpitchAngle);
}

void Camera::zoom(float factor)
{
    m_radius *= factor;
    normilizeRadius();

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

void Camera::normilizeYaw()
{
    if (m_yaw < CameraConstants::YAW_MIN) {
        m_yaw = CameraConstants::YAW_MAX;
    }
    else if (m_yaw > CameraConstants::YAW_MAX){
        m_yaw = CameraConstants::YAW_MIN;
    }
}

void Camera::normilizePitch()
{
    if (m_pitch < CameraConstants::PITCH_MIN) {
        m_pitch = CameraConstants::PITCH_MIN;
    }
    else if (m_pitch > CameraConstants::PITCH_MAX){
        m_pitch = CameraConstants::PITCH_MAX;
    }
}
void Camera::normilizeRadius()
{
    if (m_radius < CameraConstants::RADIUS_MIN) {
        m_radius = CameraConstants::RADIUS_MIN;
    }
    else if (m_radius > CameraConstants::RADIUS_MAX) {
        m_radius = CameraConstants::RADIUS_MAX;
    }
}

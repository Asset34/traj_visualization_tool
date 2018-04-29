#include "camera.hpp"

Camera::Camera()
    : m_front      (QVector3D( 0.0, -10.0, 0.0 )),
      m_center     (QVector3D( 0.0,   0.0, 0.0 )),
      m_up         (QVector3D( 0.0,   0.0, 1.0 )),
      m_yawVector  (QVector3D( 0.0,   0.0, 1.0 )),
      m_pitchVector(QVector3D(-1.0,   0.0, 0.0 ))
{
}

const QVector3D &Camera::getCenter() const
{
    return m_center;
}

void Camera::moveCenter(const QVector3D &center)
{
    m_center = center;
}

void Camera::rotateYaw(float dangle)
{
    m_yawMatrix.setToIdentity();
    m_yawMatrix.rotate(dangle, m_yawVector);

    /* Rotate camera front */
    m_front = m_yawMatrix * m_front;

    /* Rotate camera up */
    m_up = m_yawMatrix * m_up;

    /* Rotate pitch vector */
    m_pitchVector = m_yawMatrix * m_pitchVector;
}

void Camera::rotatePitch(float dangle)
{
    m_pitchMatrix.setToIdentity();
    m_pitchMatrix.rotate(dangle, m_pitchVector);

    /* Rotate camera front */
    m_front = m_pitchMatrix * m_front;

    /* Rotate camera up */
    m_up = m_pitchMatrix * m_up;

    /* Rotaate yaw vector */
    m_yawVector = m_pitchMatrix * m_yawVector;
}

void Camera::rotate(float dyawAngle, float dpitchAngle)
{
    rotateYaw(dyawAngle);
    rotatePitch(dpitchAngle);
}

void Camera::zoom(float factor)
{
    m_scaleMatrix.setToIdentity();
    m_scaleMatrix.scale(factor);

    /* Update eye */
    m_front = m_scaleMatrix * m_front;
}

QMatrix4x4 Camera::getViewMatrix() const
{
    QMatrix4x4 view;
    view.lookAt(m_center + m_front, m_center, m_up);

    return  view;
}

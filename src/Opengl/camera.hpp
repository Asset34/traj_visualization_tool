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
    void rotate(float dyawAngle, float dpitchAngle);
    void zoom(float factor);

    const QVector3D &getCenter() const;

    QMatrix4x4 getViewMatrix() const;

private:
    /* Camera vectors */
    QVector3D m_front;
    QVector3D m_center;
    QVector3D m_up;

    /* Rotate vectors */
    QVector3D m_yawVector;
    QVector3D m_pitchVector;

    /* Transform matrixes */
    QMatrix4x4 m_yawMatrix;
    QMatrix4x4 m_pitchMatrix;
    QMatrix4x4 m_scaleMatrix;
};

#endif // CAMERA_HPP

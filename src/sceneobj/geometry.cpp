#include "geometry.hpp"

namespace Geometry {

double angleBetween(const QVector3D &vec1, const QVector3D &vec2)
{
    double dotProduct = QVector3D::dotProduct(vec1, vec2);
    double angle = qRadiansToDegrees(qAcos(dotProduct / (vec1.length() * vec2.length())));

    return angle;
}

QVector3D rotateVector(const QVector3D &vec, double angle, const QVector3D &rotationVec)
{
    QMatrix4x4 rotateMatrix;
    rotateMatrix.setToIdentity();
    rotateMatrix.rotate(angle, rotationVec);

    return rotateMatrix * vec;
}

} // Geometry



#include "geometry.hpp"

namespace Geometry {

double computeAngleBetween(const QVector3D &vec1, const QVector3D &vec2)
{
    double dotProduct = QVector3D::dotProduct(vec1, vec2);
    double radianAngle = qAcos(dotProduct / (vec1.length() * vec2.length()));
    double degreeAngle = qRadiansToDegrees(radianAngle);

    return degreeAngle;
}

QVector3D rotateVector(const QVector3D &vec, double angle, const QVector3D &rotationVec)
{
    QMatrix4x4 rotateMatrix;
    rotateMatrix.setToIdentity();
    rotateMatrix.rotate(angle, rotationVec);

    return rotateMatrix * vec;
}

} // Geometry



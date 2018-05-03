#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>

#include <QtMath>

namespace Geometry {

double angleBetween(const QVector3D &vec1, const QVector3D &vec2);
QVector3D rotateVector(const QVector3D &vec, double angle, const QVector3D &rotationVec);

} // Geometry

#endif // GEOMETRY_HPP

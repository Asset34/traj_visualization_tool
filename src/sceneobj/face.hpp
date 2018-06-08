#ifndef FACE_HPP
#define FACE_HPP

#include <QPair>
#include <QVector3D>
#include <QVector>

#include "qopengl.h"
#include "geometry.hpp"
#include "section.hpp"

class Face
{
public:
    Face(const QVector3D &rightTop    = {0.0, 0.0, 0.0},
         const QVector3D &leftTop     = {0.0, 0.0, 0.0},
         const QVector3D &leftBottom  = {0.0, 0.0, 0.0},
         const QVector3D &rightBottom = {0.0, 0.0, 0.0});

    const QVector3D &getRightTop() const;
    const QVector3D &getLeftTop() const;
    const QVector3D &getLeftBottom() const;
    const QVector3D &getRightBottom() const;

    const Normal &getNormal() const;

    Edge getLeftEdge() const;
    Edge getRightEdge() const;
    Edge getTopEdge() const;
    Edge getBottomEdge() const;

    double computeDistanceTo(const QVector3D &vec) const;

    void appendToBuffer(QVector<GLfloat> &buffer);

    static int getBufferSize();

private:
    QVector3D m_rightTop;
    QVector3D m_leftTop;
    QVector3D m_leftBottom;
    QVector3D m_rightBottom;

    Normal m_normal;

    void appendVertexToBuffer(QVector<GLfloat> &buffer, const QVector3D &vec);
};

#endif // FACE_HPP

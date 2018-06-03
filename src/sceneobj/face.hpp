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
    Face(const QVector3D &rightTop,
         const QVector3D &leftTop,
         const QVector3D &leftBottom,
         const QVector3D &rightBottom);

    const QVector3D &getRightTop() const;
    const QVector3D &getLeftTop() const;
    const QVector3D &getLeftBottom() const;
    const QVector3D &getRightBottom() const;

    const Normal &getNormal() const;

    Edge getLeftEdge() const;
    Edge getRightEdge() const;
    Edge getTopEdge() const;
    Edge getBottomEdge() const;

    void setOpenglData(QVector<GLfloat> &data);

    double compDistTo(const QVector3D &v) const;
    bool isLookAt(const QVector3D &v) const;

    static int getOpenglDataCount();

private:
    QVector3D m_rightTop;
    QVector3D m_leftTop;
    QVector3D m_leftBottom;
    QVector3D m_rightBottom;

    Normal m_normal;

    void setOpenglVertex(QVector<GLfloat> &data, const QVector3D &v);
};

#endif // FACE_HPP

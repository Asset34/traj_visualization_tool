#include "face.hpp"

Face::Face(const QVector3D &rightTop,
           const QVector3D &leftTop,
           const QVector3D &leftBottom,
           const QVector3D &rightBottom)
    : m_rightTop(rightTop),
      m_leftTop(leftTop),
      m_leftBottom(leftBottom),
      m_rightBottom(rightBottom)
{
    m_normal = QVector3D::crossProduct(m_rightTop - m_rightBottom,
                                       m_leftBottom - m_rightBottom);
}

const QVector3D &Face::getRightTop() const
{
    return m_rightTop;
}

const QVector3D &Face::getLeftTop() const
{
    return m_leftTop;
}

const QVector3D &Face::getLeftBottom() const
{
    return m_leftBottom;
}

const QVector3D &Face::getRightBottom() const
{
    return m_rightBottom;
}

const Normal &Face::getNormal() const
{
    return m_normal;
}

Edge Face::getLeftEdge() const
{
    return Edge(m_leftTop, m_leftBottom);
}

Edge Face::getRightEdge() const
{
    return Edge(m_rightTop, m_rightBottom);
}

Edge Face::getTopEdge() const
{
    return Edge(m_rightTop, m_leftTop);
}

Edge Face::getBottomEdge() const
{
    return Edge(m_rightBottom, m_leftBottom);
}

void Face::setOpenglData(QVector<GLfloat> &data)
{
    setOpenglVertex(data, m_rightTop);
    setOpenglVertex(data, m_leftTop);
    setOpenglVertex(data, m_leftBottom);
    setOpenglVertex(data, m_rightBottom);
}

void Face::setOpenglVertex(QVector<GLfloat> &data, const QVector3D &v)
{
    // Add vertex
    data.push_back(v.x());
    data.push_back(v.y());
    data.push_back(v.z());

    // Add normal
    Normal norm = QVector3D::crossProduct(m_leftTop - m_rightTop, m_rightBottom - m_rightTop);
    data.push_back(norm.x());
    data.push_back(norm.y());
    data.push_back(norm.z());
}

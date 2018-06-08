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
    QVector3D vec1 = m_leftTop - m_rightTop;
    QVector3D vec2 = m_rightBottom - m_rightTop;
    m_normal = QVector3D::crossProduct(vec1, vec2);
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

double Face::computeDistanceTo(const QVector3D &vec) const
{
    double distance = QVector3D::dotProduct(m_normal, vec);

    return distance;
}

void Face::appendToBuffer(QVector<GLfloat> &buffer)
{
    appendVertexToBuffer(buffer, m_rightTop);
    appendVertexToBuffer(buffer, m_leftTop);
    appendVertexToBuffer(buffer, m_leftBottom);
    appendVertexToBuffer(buffer, m_rightBottom);
}

int Face::getBufferSize()
{
    return 24;
}

void Face::appendVertexToBuffer(QVector<GLfloat> &buffer, const QVector3D &vec)
{
    // Add vertex
    buffer.push_back(vec.x());
    buffer.push_back(vec.y());
    buffer.push_back(vec.z());

    // Add normal
    buffer.push_back(m_normal.x());
    buffer.push_back(m_normal.y());
    buffer.push_back(m_normal.z());
}

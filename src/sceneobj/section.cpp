#include "section.hpp"

Section::Section(QTextStream &stream, const QVector3D &point, const QVector3D &normal)
    : m_point(point),
      m_normal(normal)
{
    /* Load plane data */
    QList<QVector3D> vertices;
    float x, y;
    while (!stream.atEnd()) {
        stream >> x;
        stream >> y;
        vertices.push_back({x, y, 0.0});
    }
    m_vertices = vertices.toVector();

    /* Transform data */
    setPlane(point, normal);
}

const QVector3D &Section::getPoint() const
{
    return m_point;
}

void Section::setPoint(const QVector3D &point)
{
    updatePoint(point);
    m_point = point;
}

const Normal &Section::getNormal() const
{
    return m_normal;
}

void Section::setNormal(const QVector3D &normal)
{
    updateNormal(normal);
    m_normal = normal.normalized();
}

void Section::setPlane(const QVector3D &point, const QVector3D &normal)
{
    setPoint(point);
    setNormal(normal);
}

void Section::invert()
{
    m_normal *= -1;
}

Section Section::inverted() const
{
    Section invertedSection = *this;
    invertedSection.invert();

    return invertedSection;
}

double Section::computeDistanceToPoint(const QVector3D &point) const
{
    double distance = QVector3D::dotProduct(m_normal, point);

    return distance;
}

int Section::getVertexCount() const
{
    return m_vertices.count();
}

const QVector3D &Section::getVertexAt(int index) const
{
    return m_vertices.at(index);
}

const QVector3D &Section::getFirstVertex() const
{
    return m_vertices.first();
}

const QVector3D &Section::getLastVertex() const
{
    return m_vertices.last();
}

const Edge Section::getEdgeAt(int index) const
{
    if (index == m_vertices.count() - 1) {
        return Edge(m_vertices.first(), m_vertices.last());
    }
    else {
        return Edge(m_vertices.at(index + 1), m_vertices.at(index));
    }
}

void Section::updatePoint(const QVector3D &point)
{
    QVector3D displacementVec = point - m_point;

    for (int i = 0; i < m_vertices.count(); i++) {
        m_vertices[i] += displacementVec;
    }
}

void Section::updateNormal(const Normal &normal)
{
    QVector3D rotationVec = QVector3D::crossProduct(m_normal, normal);
    double rotationAngle = Geometry::computeAngleBetween(m_normal, normal);

    QVector3D radiusVec, rotatedVec;
    for (int i = 0; i < m_vertices.count(); i++) {
        radiusVec = m_vertices[i] - m_point;
        rotatedVec = Geometry::rotateVector(radiusVec, rotationAngle, rotationVec);
        m_vertices[i] = m_point + rotatedVec;
    }
}

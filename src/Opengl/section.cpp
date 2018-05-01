#include "section.hpp"

Section::Section(QTextStream &stream, const QVector3D &coord, const QVector3D &normal)
    : m_coord(coord),
      m_normal(normal)
{
    /* Load plane data */
    float x, y;
    while (!stream.atEnd()) {
        stream >> x;
        stream >> y;
        m_data.push_back({x, y, 0.0});
    }

    /* Set default plane values */
    m_coord = {0.0, 0.0, 0.0};
    m_normal = {0.0, 0.0, 1.0};

    /* Transform data */
    setPlane(coord, normal);
}

const QVector3D &Section::operator[](int index) const
{
    return m_data.at(index);
}

void Section::setCoord(const QVector3D &coord)
{
    updateCoord(coord);
    m_coord = coord;
}

void Section::setNormal(const QVector3D &normal)
{
    updateNormal(normal);
    m_normal = normal.normalized();
}

void Section::setPlane(const QVector3D &coord, const QVector3D &normal)
{
    setCoord(coord);
    setNormal(normal);
}

int Section::getCount() const
{
    return m_data.count();
}

void Section::updateCoord(const QVector3D &coord)
{
    QVector3D displacementVec = coord - m_coord;
    for (int i = 0; i < m_data.count(); i++) {
        m_data[i] += displacementVec;
    }
}

void Section::updateNormal(const QVector3D &normal)
{
    QVector3D rotationVec = QVector3D::crossProduct(m_normal, normal);
    double rotationAngle = Geometry::angleBetween(m_normal, normal);
    for (int i = 0; i < m_data.count(); i++) {
        m_data[i] = m_coord + Geometry::rotateVector(m_data[i] - m_coord, rotationAngle, rotationVec);
    }
}

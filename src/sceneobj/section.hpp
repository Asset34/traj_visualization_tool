#ifndef SECTION_HPP
#define SECTION_HPP

#include <QTextStream>

#include <QList>

#include <QVector3D>

#include "geometry.hpp"

class Section
{
public:
    explicit Section(QTextStream &stream,
                     const QVector3D &point = {0.0, 0.0, 0.0},
                     const QVector3D &normal = {0.0, 0.0, 1.0});

    int getVertexCount() const;

    const QVector3D &getVertexAt(int index) const;
    const QVector3D &getFirstVertex() const;
    const QVector3D &getLastVertex() const;

    const Edge getEdgeAt(int index) const;

    const QVector3D &getPoint() const;
    void setPoint(const QVector3D &point);

    const Normal &getNormal() const;
    void setNormal(const QVector3D &normal);

    void setPlane(const QVector3D &point, const QVector3D &normal);

    void invert();
    Section inverted() const;

    double computeDistanceToPoint(const QVector3D &point) const;

private:
    QVector3D m_point;
    Normal m_normal;
    QVector<QVector3D> m_vertices;

    void updatePoint(const QVector3D &point);
    void updateNormal(const Normal &normal);
};

#endif // SECTION_HPP

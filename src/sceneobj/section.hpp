#ifndef SECTION_HPP
#define SECTION_HPP

#include <QList>

#include <QTextStream>

#include <QVector2D>
#include <QVector3D>

#include "geometry.hpp"

class Section
{
public:
    explicit Section(QTextStream &stream,
                     const QVector3D &coord = {0.0, 0.0, 0.0},
                     const QVector3D &normal = {0.0, 0.0, 1.0});

    int getCount() const;

    const QVector3D &getFirstVertex() const;
    const QVector3D &getLastVertex() const;

    const QVector3D &getCoord() const;
    const Normal &getNormal() const;

    const QVector3D &getVertexAt(int index) const;

    void setCoord(const QVector3D &coord);
    void setNormal(const QVector3D &normal);
    void setPlane(const QVector3D &coord, const QVector3D &normal);

    void invert();

    double computeDistToPoint(const QVector3D &v) const;

private:
    QVector3D m_coord;
    Normal m_normal;
    QList<QVector3D> m_data;

    void updateCoord(const QVector3D &coord);
    void updateNormal(const Normal &normal);
};

#endif // SECTION_HPP

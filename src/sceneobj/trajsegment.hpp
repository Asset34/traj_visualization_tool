#ifndef TRAJSEGMENT_HPP
#define TRAJSEGMENT_HPP

#include <QList>
#include <QVector3D>

#include "climits"

#include "geometry.hpp"
#include "section.hpp"
#include "face.hpp"

class TrajSegment
{
public:
    TrajSegment(const Section &bottom, const Section &top);

    int getVertexCount() const;
    int getSectionVertexCount() const;
    int getFaceCount() const;
    int getSideFaceCount() const;
    int getEdgeCount() const;

    const QVector3D &getVertexAt(int index) const;
    const Edge &getEdgeAt(int index) const;
    const Face &getSideFaceAt(int index) const;
    const Section &getBottom() const;
    const Section &getTop() const;

    Interval getDistIntervalTo(const Normal &norm) const;

    void setOpenGLData(QVector<GLfloat> &data);

    bool isOverlap(const Face &face) const;

    static bool isCollide(const TrajSegment &s1, const TrajSegment &s2);

private:
    Section m_bottom;
    Section m_top;

    QVector<QVector3D> m_vertices;
    QVector<Edge> m_edges;
    QList<Face> m_sideFaces;

    static bool isOverlap(const TrajSegment &s1, const TrajSegment &s2);
    static bool isOverlapAdditional(const TrajSegment &s1, const TrajSegment &s2);
};

#endif // TRAJSEGMENT_HPP

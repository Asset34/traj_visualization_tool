#ifndef TRAJSEGMENT_HPP
#define TRAJSEGMENT_HPP

#include <QVector>

#include <QColor>

#include <QVector3D>

#include "geometry.hpp"
#include "section.hpp"
#include "face.hpp"

class TrajSegment
{
public:
    TrajSegment(const Section &bottom, const Section &top);

    int getVertexCount() const;
    int getFaceCount() const;
    int getSideFaceCount() const;
    int getEdgeCount() const;

    int getBufferSize() const;

    const QVector3D &getVertexAt(int index) const;
    const Edge &getEdgeAt(int index) const;
    const Face &getSideFaceAt(int index) const;
    const Section &getBottom() const;
    const Section &getTop() const;

    QVector3D getEdgeVecAt(int index) const;

    Interval computeDistanceIntervalTo(const Normal &norm) const;

    void appendToBuffer(QVector<GLfloat> &buffer);

    bool detectCollisionTo(const Face &face) const;
    bool detectCollisionTo(const TrajSegment &s) const;

    static bool detectFullCollision(const TrajSegment &s1, const TrajSegment &s2);

private:
    Section m_bottom;
    Section m_top;

    QVector<QVector3D> m_vertices;
    QVector<Edge> m_edges;
    QVector<Face> m_sideFaces;

    void addVertices();
    void addFaces();
    void addEdges();

    void addVerticesFrom(const Section &s);
    void addFacesBetween(const Section &s1, const Section &s2);
    void addEdgesFrom(const Section &s);
    void addEdgesBetween(const Section &s1, const Section &s2);

    static bool detectCollision(const TrajSegment &s1, const TrajSegment &s2);
    static bool detectAdditionalCollision(const TrajSegment &s1, const TrajSegment &s2);
};

#endif // TRAJSEGMENT_HPP

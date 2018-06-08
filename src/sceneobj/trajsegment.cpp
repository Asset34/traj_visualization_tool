#include "trajsegment.hpp"

TrajSegment::TrajSegment(const Section &bottom, const Section &top)
    : m_bottom(bottom.inverted()),
      m_top(top)
{
    addVertices();
    addFaces();
    addEdges();
}

int TrajSegment::getVertexCount() const
{
    return m_vertices.count();
}

int TrajSegment::getFaceCount() const
{
    return 2 + m_sideFaces.count();
}

int TrajSegment::getSideFaceCount() const
{
    return m_sideFaces.count();
}

int TrajSegment::getEdgeCount() const
{
    return m_edges.count();
}

int TrajSegment::getBufferSize() const
{
    return Face::getBufferSize() * m_sideFaces.count();
}

const QVector3D &TrajSegment::getVertexAt(int index) const
{
    return m_vertices.at(index);
}

const Edge &TrajSegment::getEdgeAt(int index) const
{
    return m_edges.at(index);
}

QVector3D TrajSegment::getEdgeVecAt(int index) const
{
    Edge edge = m_edges.at(index);

    return edge.second - edge.first;
}

const Face &TrajSegment::getSideFaceAt(int index) const
{
    return m_sideFaces.at(index);
}

const Section &TrajSegment::getBottom() const
{
    return m_bottom;
}

const Section &TrajSegment::getTop() const
{
    return m_top;
}

Interval TrajSegment::computeDistanceIntervalTo(const Normal &norm) const
{
    /* Compute distance from each vertex to normal */
    QVector<double> distances(m_vertices.count());
    for (int i = 0; i < m_vertices.count(); i++) {
        distances[i] = QVector3D::dotProduct(norm, m_vertices[i]);
    }

    /* Get min-max interval of distances */
    auto minmax = std::minmax_element(distances.begin(), distances.end());

    return Interval(*minmax.first, *minmax.second);
}

void TrajSegment::appendToBuffer(QVector<GLfloat> &buffer)
{
    for (int i = 0; i < m_sideFaces.count(); i++) {
        m_sideFaces[i].appendToBuffer(buffer);
    }
}

bool TrajSegment::detectCollisionTo(const Face &face) const
{
    bool isLookAt;
    for (int i = 0; i < m_vertices.count(); i++) {
        isLookAt = face.computeDistanceTo(m_vertices[i]) > 0;
        if (!isLookAt) {
            return true;
        }
    }

    return false;
}

bool TrajSegment::detectCollisionTo(const TrajSegment &s) const
{
    for (int i = 0; i < s.m_sideFaces.count(); i++) {
        if (!detectCollisionTo(s.m_sideFaces[i])) {
            return false;
        }
    }

    return true;
}

bool TrajSegment::detectFullCollision(const TrajSegment &s1, const TrajSegment &s2)
{
    bool isDetected = detectCollision(s1, s2);
    bool isDetectedAdditional = detectAdditionalCollision(s1, s2);

    return isDetected || isDetectedAdditional;
}

void TrajSegment::addVertices()
{
    m_vertices.reserve(2 * m_bottom.getVertexCount());

    addVerticesFrom(m_bottom);
    addVerticesFrom(m_top);
}

void TrajSegment::addFaces()
{
    m_sideFaces.reserve(m_bottom.getVertexCount());

    addFacesBetween(m_bottom, m_top);
}

void TrajSegment::addEdges()
{
    m_edges.reserve(3 * m_bottom.getVertexCount());

    addEdgesFrom(m_bottom);
    addEdgesFrom(m_top);
    addEdgesBetween(m_bottom, m_top);
}

void TrajSegment::addVerticesFrom(const Section &s)
{
    for (int i = 0; i < s.getVertexCount(); i++) {
        m_vertices.push_back(s.getVertexAt(i));
    }
}

void TrajSegment::addFacesBetween(const Section &s1, const Section &s2)
{
    Face face;
    for (int i = 1; i < s1.getVertexCount(); i++) {
        face = Face(s2.getVertexAt(i),
                    s2.getVertexAt(i - 1),
                    s1.getVertexAt(i - 1),
                    s1.getVertexAt(i));
        m_sideFaces.push_back(face);
    }

    /* Add last face */
    face = Face(s2.getFirstVertex(),
                s2.getLastVertex(),
                s1.getLastVertex(),
                s1.getFirstVertex());
    m_sideFaces.push_back(face);
}

void TrajSegment::addEdgesFrom(const Section &s)
{
    for (int i = 0; i < s.getVertexCount(); i++) {
        m_edges.push_back(s.getEdgeAt(i));
    }
}

void TrajSegment::addEdgesBetween(const Section &s1, const Section &s2)
{
    Edge edge;
    for (int i = 0; i < s1.getVertexCount(); i++) {
        edge = Edge(s1.getVertexAt(i), s2.getVertexAt(i));
        m_edges.push_back(edge);
    }
}

bool TrajSegment::detectCollision(const TrajSegment &s1, const TrajSegment &s2)
{
    bool isDetected12 = s1.detectCollisionTo(s2);
    bool isDetected21 = s2.detectCollisionTo(s1);

    return isDetected12 && isDetected21;
}

bool TrajSegment::detectAdditionalCollision(const TrajSegment &s1, const TrajSegment &s2)
{
    Normal norm;
    QVector3D edgeVec1, edgeVec2;
    Interval inter1, inter2;
    for (int i = 0; i < s1.m_edges.count(); i++) {
        for (int j = 0; j < s2.m_edges.count(); j++) {
            edgeVec1 = s1.getEdgeVecAt(i);
            edgeVec2 = s2.getEdgeVecAt(j);
            norm = QVector3D::crossProduct(edgeVec1, edgeVec2);

            inter1 = s1.computeDistanceIntervalTo(norm);
            inter2 = s2.computeDistanceIntervalTo(norm);

            if (inter1.first > inter2.second ||
                inter2.first > inter1.second) {
                return false;
            }
        }
    }

    return true;
}

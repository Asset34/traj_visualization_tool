#include "trajsegment.hpp"

TrajSegment::TrajSegment(const Section &bottom, const Section &top)
    : m_bottom(bottom),
      m_top(top)
{
    m_bottom.invert();

    /* Set vertices */
    m_vertices.reserve(2 * bottom.getCount());
    for (int i = 0; i < bottom.getCount(); i++) {
        m_vertices.push_back(bottom.getVertexAt(i));
    }
    for (int i = 0; i < top.getCount(); i++) {
        m_vertices.push_back(top.getVertexAt(i));
    }

    /* Set faces */
    for (int i = 1; i < bottom.getCount(); i++) {
        m_sideFaces.push_back(Face(top.getVertexAt(i),
                                   top.getVertexAt(i - 1),
                                   bottom.getVertexAt(i - 1),
                                   bottom.getVertexAt(i)));
    }
    m_sideFaces.push_back(Face(top.getFirstVertex(),
                               top.getLastVertex(),
                               bottom.getLastVertex(),
                               bottom.getFirstVertex()));

    /* Set edges */
    m_edges.reserve(3 * bottom.getCount());
    for (int i = 0; i < m_sideFaces.count(); i++) {
        m_edges.push_back(m_sideFaces[i].getTopEdge());
        m_edges.push_back(m_sideFaces[i].getLeftEdge());
        m_edges.push_back(m_sideFaces[i].getBottomEdge());
    }
}

int TrajSegment::getVertexCount() const
{
    return m_vertices.count();
}

int TrajSegment::getSectionVertexCount() const
{
    return m_bottom.getCount();
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

int TrajSegment::getOpenglDataCount() const
{
    return Face::getOpenglDataCount() * m_sideFaces.count();
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

Interval TrajSegment::getDistIntervalTo(const Normal &norm) const
{
    QVector<double> distances(m_vertices.count());
    for (int i = 0; i < m_vertices.count(); i++) {
        distances[i] = QVector3D::dotProduct(norm, m_vertices[i]);
    }

    auto minmax = std::minmax_element(distances.begin(), distances.end());
    return Interval(*minmax.first, *minmax.second);
}

void TrajSegment::setOpenGLData(QVector<GLfloat> &data)
{
    for (int i = 0; i < m_sideFaces.count(); i++) {
        m_sideFaces[i].setOpenglData(data);
    }
}

bool TrajSegment::isOverlap(const Face &face) const
{
    QVector3D v;
    for (int i = 0; i < m_vertices.count(); i++) {
        if (!face.isLookAt(m_vertices[i])) {
            return true;
        }
    }

    return false;
}

bool TrajSegment::isCollide(const TrajSegment &s1, const TrajSegment &s2)
{
    return isOverlap(s1, s2) || isOverlapAdditional(s1, s2);
}

bool TrajSegment::isOverlap(const TrajSegment &s1, const TrajSegment &s2)
{
    /* Check from first to second */
    for (int i = 0; i < s1.m_sideFaces.count(); i++) {
        Face face = s1.m_sideFaces[i];
        if (!s2.isOverlap(face)) {
            return false;
        }
    }

    /* Check from second to first */
    for (int i = 0; i < s2.m_sideFaces.count(); i++) {
        Face face = s2.m_sideFaces[i];
        if (!s1.isOverlap(face)) {
            return false;
        }
    }

    return true;
}

bool TrajSegment::isOverlapAdditional(const TrajSegment &s1, const TrajSegment &s2)
{
    Normal norm;
    QVector3D edgeVec1, edgeVec2;
    Interval inter1, inter2;
    for (int i = 0; i < s1.m_edges.count(); i++) {
        for (int j = 0; j < s2.m_edges.count(); j++) {
            edgeVec1 = s1.getEdgeVecAt(i);
            edgeVec2 = s2.getEdgeVecAt(i);
            norm = QVector3D::crossProduct(edgeVec1, edgeVec2);

            inter1 = s1.getDistIntervalTo(norm);
            inter2 = s2.getDistIntervalTo(norm);

            if (inter1.first > inter2.second || inter2.first > inter1.second) {
                return false;
            }
        }
    }

    return true;
}

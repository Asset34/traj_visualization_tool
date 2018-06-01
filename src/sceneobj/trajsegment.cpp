#include "trajsegment.hpp"

TrajSegment::TrajSegment(const Section &bottom, const Section &top)
    : m_bottom(bottom),
      m_top(top)
{
    m_bottom.invert();

    for (int i = 1; i < bottom.getCount(); i++) {
        m_faces.push_back(Face(top.getVertexAt(i),
                               top.getVertexAt(i - 1),
                               bottom.getVertexAt(i - 1),
                               bottom.getVertexAt(i)));
    }
    m_faces.push_back(Face(top.getFirstVertex(),
                           top.getLastVertex(),
                           bottom.getLastVertex(),
                           bottom.getFirstVertex()));
}

int TrajSegment::getFaceCount() const
{
    return m_faces.count();
}

const Face &TrajSegment::getFaceAt(int index)
{
    return m_faces.at(index);
}

const Normal &TrajSegment::getFaceNormalAt(int index) const
{
    return m_faces[index].getNormal();
}

const Normal &TrajSegment::getBottomNormal() const
{
    return m_bottom.getNormal();
}

const Normal &TrajSegment::getTopNormal() const
{
    return m_top.getNormal();
}

void TrajSegment::setOpenGLData(QVector<GLfloat> &data)
{
    for (int i = 0; i < m_faces.count(); i++) {
        m_faces[i].setOpenglData(data);
    }
}

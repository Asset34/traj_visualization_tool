#ifndef TRAJSEGMENT_HPP
#define TRAJSEGMENT_HPP

#include <QList>
#include <QVector3D>

#include "geometry.hpp"
#include "section.hpp"
#include "face.hpp"

class TrajSegment
{
public:
    TrajSegment(const Section &bottom, const Section &top);

    int getFaceCount() const;
    const Face &getFaceAt(int index);

    const Normal &getFaceNormalAt(int index) const;
    const Normal &getBottomNormal() const;
    const Normal &getTopNormal() const;

    void setOpenGLData(QVector<GLfloat> &data);

private:
    Section m_bottom;
    Section m_top;

    QList<Face> m_faces;
};

#endif // TRAJSEGMENT_HPP

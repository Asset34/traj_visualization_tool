#ifndef PTRAJ_HPP
#define PTRAJ_HPP

#include <QTextStream>
#include <QVector>
#include <QVector3D>
#include <QColor>

#include "qopengl.h"
#include "section.hpp"

class Traj
{
public:
    Traj(QTextStream &stream, const Section &section);

    int getTrajVertexCount() const;
    int getVertexCount() const;
    int getVertexCount(double time) const;
    int getCount() const;
    int getCount(double time) const;

    double getBeginTime() const;
    double getEndTime() const;
    double getTimeStep() const;

    const QVector3D &getAverage() const;
    const GLfloat *getConstData() const;

    const QColor &getColor() const;
    void setColor(const QColor &color);

    bool isDisplayed() const;
    void setDisplayed(bool flag);
    void setDisplayed(Qt::CheckState state);

    void setSection(const Section &section);

private:
    double m_timeBegin;
    double m_timeEnd;
    int m_valPerSec;

    bool m_displayFlag;
    QColor m_color;
    QVector3D m_average;

    Section m_section;
    QVector<QVector3D> m_trajData;
    QVector<GLfloat> m_data;

    void setData();
    void setAverage();

    void addQuads(const Section &s1, const Section &s2);
    void addQuad(const QVector3D &vec1, const QVector3D &vec2, const QVector3D &vec3, const QVector3D &vec4);
    void addVector(const QVector3D &vec);
};

namespace TrajUtills {

double generalBeginTime(const QList<Traj*> &trajs);
double generalEndTime(const QList<Traj*> &trajs);
double generalTimeStep(const QList<Traj*> &trajs);

} // TrajUtills

#endif // PTRAJ_HPP

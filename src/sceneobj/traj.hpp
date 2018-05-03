#ifndef PTRAJ_HPP
#define PTRAJ_HPP

#include <QVector>
#include <QTextStream>
#include <QVector3D>
#include <QColor>

#include "qopengl.h"
#include "section.hpp"

class Traj
{
public:
    Traj(const QString &name, QTextStream &stream, const Section &section);

    int getTrajVertexCount() const;
    int getVertexCount() const;
    int getVertexCount(double time) const;
    int getCount() const;
    int getCount(double time) const;

    double getBeginTime() const;
    double getEndTime() const;
    double getTimeStep() const;

    const QString &getName() const;
    void setName(const QString &name);

    const QVector3D &getColorVector() const;
    QColor getColor() const;
    void setColor(const QVector3D &color);
    void setColor(const QColor &color);

    const QVector3D &getAverage() const;

    bool isDisplayed() const;
    void setDisplayed(bool flag);
    void setDisplayed(Qt::CheckState state);

    const GLfloat *getConstData() const;

private:
    double m_timeBegin;
    double m_timeEnd;
    int m_valPerSec;

    QString m_name;
    QVector3D m_color;
    QVector3D m_average;

    bool m_displayFlag;

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

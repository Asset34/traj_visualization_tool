#ifndef PTRAJ_HPP
#define PTRAJ_HPP

#include <QTextStream>
#include <QVector3D>
#include <QColor>

#include <QVector>
#include <QList>

#include "qopengl.h"
#include "section.hpp"
#include "trajsegment.hpp"

typedef QVector3D Color;

class Traj
{
public:
    Traj(const QString &name, QTextStream &stream, const Section &section);

    int getVertexCount() const;
    int getVertexCount(double time) const;
    int getOpenglDataCount() const;
    int getOpenglDataCount(double time) const;
    int getSegmentsCount() const;

    double getBeginTime() const;
    double getEndTime() const;
    double getTimeStep() const;

    const QString &getName() const;
    void setName(const QString &name);

    QColor getColor() const;
    void setColor(const QColor &color);
    const Color &getColorVec() const;
    const Color &getBottomColor() const;
    const Color &getTopCollor() const;

    const QVector3D &getBarycenter() const;

    const QVector3D &getInitials() const;

    int getTimeBorder() const;
    void setTimeBorder(int time);
    void setTimeBorderAtSegment(int index);

    bool isDisplayed() const;
    void setDisplayed(bool status);
    bool isCollisionMapped() const;
    void setCollisionMapped(bool status);

    const TrajSegment &getSegmentAt(int index) const;

    const GLfloat *getConstData() const;

private:
    QString m_name;
    QVector3D m_barycenter;
    int m_timeBorder;

    /* Time attributes */
    double m_timeBegin;
    double m_timeEnd;
    int m_valPerSec;

    /* Color attributes */
    Color m_color;
    Color m_collisionColor;
    Color m_notcollisionCollor;

    /* Flags */
    bool m_isDisplayed;
    bool m_isCollisionMapped;

    /* Data */
    Section m_section;
    QVector<QVector3D> m_trajData;
    QList<TrajSegment> m_segments;
    QVector<GLfloat> m_data;

    void setData();
    void setBarycenter();
};

namespace TrajUtills {

double compGeneralBeginTime(const QList<Traj*> &trajs);
double compGeneralEndTime(const QList<Traj*> &trajs);
double compGeneralTimeStep(const QList<Traj*> &trajs);

// Note: Only for trajectories with the same time attributes
int compGeneralCollisionTimeBorder(const QList<Traj*> &trajs);

} // TrajUtills

#endif // PTRAJ_HPP

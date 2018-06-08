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
    int getSegmentCount() const;

    int getBufferSize() const;
    int getBufferSize(double time) const;

    double getBeginTime() const;
    double getEndTime() const;
    double getTimeStep() const;

    const QString &getName() const;
    void setName(const QString &name);

    QColor getColor() const;
    void setColor(const QColor &color);
    const Color &getColorVec() const;  
    const Color &getColorBelowTimeBorder() const;
    const Color &getColorAboveTimeBorder() const;

    const QVector3D &getBarycenter() const;

    const QVector3D &getInitials() const;
    QString getStringInitials() const;

    int getTimeBorder() const;
    void setTimeBorder(double time);
    void setTimeBorderAtSegment(int index);

    bool isDisplayed() const;
    void setDisplayed(bool status);
    bool isCollisionMapped() const;
    void setCollisionMapped(bool status);

    const GLfloat *getBufferData() const;

    static bool detectSegmentCollision(const Traj &t1, const Traj &t2, int segmentIndex);

private:
    QString m_name;
    Section m_section;
    QVector3D m_barycenter;

    /* Time attributes */
    double m_timeBegin;
    double m_timeEnd;
    int m_valPerSec;

    double m_timeBorder;

    /* Color attributes */
    Color m_color;
    Color m_belowColor;
    Color m_aboveColor;

    /* Flags */
    bool m_isDisplayed;
    bool m_isCollisionMapped;

    /* Data */
    QVector<QVector3D> m_trajVertices;
    QList<TrajSegment> m_segments;
    QVector<GLfloat> m_bufferData;

    void addTimeAttributes(QTextStream &stream);
    void addTrajVertices(QTextStream &stream);

    void computeBufferData();
    void computeBarycenter();
};

namespace TrajUtills {

double computeGeneralBeginTime(const QList<Traj*> &trajs);
double computeGeneralEndTime(const QList<Traj*> &trajs);
double computeGeneralTimeStep(const QList<Traj*> &trajs);

// Note: Only for trajectories with the same time attributes
int computeCollisionSegmentIndex(const QList<Traj*> &trajs);

} // TrajUtills

#endif // PTRAJ_HPP

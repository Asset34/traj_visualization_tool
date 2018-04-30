#ifndef PTRAJ_HPP
#define PTRAJ_HPP

#include <QColor>

#include <QVector3D>
#include <QList>

#include <QFile>
#include <QTextStream>

#include <QDebug>

#include "qopengl.h"

class Traj
{
public:
    explicit Traj(const QString &name,
                  double timeBegin,
                  double timeEnd,
                  int pointPerSec,
                  bool displayStatus = true,
                  const QColor &color = Qt::white);

    const QVector3D &get(double time) const;

    double getBeginTime() const;
    double getEndTime() const;
    double getTimeStep() const;

    int getDataCount() const;
    int getDataCount(double time) const;
    int getVertexCount() const;
    int getVertexCount(double time) const;

    bool getDisplayStatus() const;
    void setDisplayStatus(bool status);
    void setDisplayStatus(Qt::CheckState state);

    const QString &getName() const;

    const QColor &getColor() const;
    void setColor(const QColor &color);

    QVector3D getAverage() const;

    GLfloat *getOpenglData() const;

    void add(float x, float y, float z);

private:
    double m_timeBegin;
    double m_timeEnd;
    int m_pointPerSec;
    bool m_displayStatus;

    QString m_name;
    QColor m_color;

    QList<QVector3D> m_data;

};

namespace TrajUtills {

Traj *readTraj(const QString &name, const QString &path);
double getMinBeginTime(const QList<Traj*> &trajList);
double getMaxEndTime(const QList<Traj*> &trajList);
double getMinTimeStep(const QList<Traj*> &trajList);

} // TrajUtills


#endif // PTRAJ_HPP

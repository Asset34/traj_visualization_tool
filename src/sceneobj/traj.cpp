#include "traj.hpp"

Traj::Traj(const QString &name, QTextStream &stream, const Section &section)
    : m_name(name),
      m_section(section)
{
    /* Load trajectory time values */
    m_timeBegin = stream.readLine().toDouble();
    m_timeEnd = stream.readLine().toDouble();
    m_valPerSec = stream.readLine().toDouble();

    /* Load trajectory data */
    int trajDataSize = (m_timeEnd - m_timeBegin) * m_valPerSec + 1;
    m_trajData.reserve(trajDataSize);
    QStringList values;
    while (!stream.atEnd()) {
        values = stream.readLine().split(',');

        m_trajData.push_back({values.at(0).toFloat(),
                              values.at(1).toFloat(),
                              values.at(2).toFloat()});
    }

    /* Set some initial attributes */
    m_collisionColor = {1.0, 0.0, 0.0};
    m_notcollisionCollor = {1.0, 1.0, 1.0};
    m_isDisplayed = true;
    m_isCollisionMapped = false;
    m_timeBorder = 0;
    setBarycenter();
    setData();
}

int Traj::getVertexCount() const
{
    return m_trajData.count();
}

int Traj::getVertexCount(double time) const
{
    return (time - m_timeBegin) * m_valPerSec * m_section.getCount() * 4;
}

int Traj::getOpenglDataCount() const
{
    return m_data.count();
}

int Traj::getOpenglDataCount(double time) const
{
    return getVertexCount(time) * m_segments[0].getOpenglDataCount();
}

int Traj::getSegmentsCount() const
{
    return m_segments.count();
}

double Traj::getBeginTime() const
{
    return m_timeBegin;
}

double Traj::getEndTime() const
{
    return m_timeEnd;
}

double Traj::getTimeStep() const
{
    return 1.0 / m_valPerSec;
}

const QString &Traj::getName() const
{
    return m_name;
}

void Traj::setName(const QString &name)
{
    m_name = name;
}

QColor Traj::getColor() const
{
    QColor color;
    color.setRedF(m_color.x());
    color.setGreenF(m_color.y());
    color.setBlueF(m_color.z());

    return color;
}

void Traj::setColor(const QColor &color)
{
    m_color = {float(color.redF()),
               float(color.greenF()),
               float(color.blueF())};
}

const Color &Traj::getColorVec() const
{
    return m_color;
}

const Color &Traj::getBottomColor() const
{
    return m_collisionColor;
}

const Color &Traj::getTopCollor() const
{
    return m_notcollisionCollor;
}

void Traj::setColorVec(const QVector3D &color)
{
    m_color = color;
}

const QVector3D &Traj::getBarycenter() const
{
    return m_barycenter;
}

int Traj::getTimeBorder() const
{
    return m_timeBorder;
}

void Traj::setTimeBorder(int time)
{
    m_timeBorder = time;
}

void Traj::setTimeBorderAtSegment(int index)
{
    m_timeBorder = m_timeBegin + index * getTimeStep();
}

bool Traj::isDisplayed() const
{
    return m_isDisplayed;
}

void Traj::setDisplayed(bool status)
{
    m_isDisplayed = status;
}

bool Traj::isCollisionMapped() const
{
    return m_isCollisionMapped;
}

void Traj::setCollisionMapped(bool status)
{
    m_isCollisionMapped = status;
}

const TrajSegment &Traj::getSegmentAt(int index) const
{
    return m_segments.at(index);
}

const GLfloat *Traj::getConstData() const
{
    return m_data.constData();
}

void Traj::setData()
{
    /* Reset data */
    int size = 2 * (m_trajData.count() - 1) * m_section.getCount() * 4 * 3;
    m_data.clear();
    m_data.reserve(size);

    Normal norm;

    /* Get initial data */
    if (m_trajData.count() >= 2) {
        norm = m_trajData[1] - m_trajData[0];
        m_section.setPlane(m_trajData[0], norm);
    }

    /* Get the rest data */
    for (int i = 2; i < m_trajData.count(); i++) {
        norm = m_trajData[i] - m_trajData[i - 1];

        Section prevSection = m_section;
        m_section.setPlane(m_trajData[i - 1], norm);

        TrajSegment segment(prevSection, m_section);
        m_segments.push_back(segment);
        segment.setOpenGLData(m_data);
    }

    /* Get last data */
    Section prevSection = m_section;
    m_section.setPlane(m_trajData.last(), norm);
    TrajSegment segment(prevSection, m_section);
    m_segments.push_back(segment);
    segment.setOpenGLData(m_data);
}

void Traj::setBarycenter()
{
    QVector3D sum = {0.0, 0.0, 0.0};
    for (int i = 0; i < m_trajData.count(); i++) {
        sum += m_trajData[i];
    }

    m_barycenter = sum / m_trajData.count();
}

namespace TrajUtills {

double compGeneralBeginTime(const QList<Traj*> &trajs)
{
    double time = trajs.first()->getBeginTime();

    for (int i = 1; i < trajs.count(); i++) {
        if (trajs[i]->getBeginTime() < time) {
            time = trajs[i]->getBeginTime();
        }
    }

    return time;
}

double compGeneralEndTime(const QList<Traj*> &trajs)
{
    double time = trajs.first()->getEndTime();

    for (int i = 1; i < trajs.count(); i++) {
        if (trajs[i]->getEndTime() > time) {
            time = trajs[i]->getEndTime();
        }
    }

    return time;
}

double compGeneralTimeStep(const QList<Traj*> &trajs)
{
    double step = trajs.first()->getTimeStep();

    for (int i = 1; i < trajs.count(); i++) {
        if (trajs[i]->getTimeStep() < step) {
            step = trajs[i]->getTimeStep();
        }
    }

    return step;
}

int compGeneralCollisionTimeBorder(const QList<Traj*> &trajs)
{
    bool check;
    for (int i = 0; i < trajs[0]->getSegmentsCount(); i++) {
        for (int j = 0; j < trajs.count(); j++) {
            for (int k = j + 1; k < trajs.count(); k++) {
                check = TrajSegment::isCollide(trajs[j]->getSegmentAt(i),
                                               trajs[k]->getSegmentAt(i));
                if(!check) {
                    return i - 1;
                }
            }
        }
    }

    return trajs[0]->getSegmentsCount() - 1;
}

} // TrajUtills

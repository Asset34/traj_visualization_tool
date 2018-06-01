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

    setAverage();
    setData();
}

int Traj::getTrajVertexCount() const
{
    return m_trajData.count();
}

int Traj::getVertexCount() const
{
    return getCount() / 3;
}

int Traj::getVertexCount(double time) const
{
    return (time - m_timeBegin) * m_valPerSec * m_section.getCount() * 4;
}

int Traj::getCount() const
{
    return m_data.count();
}

int Traj::getCount(double time) const
{
    return getVertexCount(time) * 3;
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

const QVector3D &Traj::getColorVector() const
{
    return m_color;
}

QColor Traj::getColor() const
{
    QColor color;
    color.setRedF(m_color.x());
    color.setGreenF(m_color.y());
    color.setBlueF(m_color.z());

    return color;
}

void Traj::setColor(const QVector3D &color)
{
    m_color = color;
}

void Traj::setColor(const QColor &color)
{
    m_color = {float(color.redF()),
               float(color.greenF()),
               float(color.blueF())};
}

const QVector3D &Traj::getAverage() const
{
    return m_average;
}

bool Traj::isDisplayed() const
{
    return m_displayFlag;
}

void Traj::setDisplayed(bool flag)
{
    m_displayFlag = flag;
}

void Traj::setDisplayed(Qt::CheckState state)
{
    if (state == Qt::Checked) {
        m_displayFlag = true;
    }
    else {
        m_displayFlag = false;
    }
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

void Traj::setAverage()
{
    QVector3D sum = {0.0, 0.0, 0.0};
    for (int i = 0; i < m_trajData.count(); i++) {
        sum += m_trajData[i];
    }

    m_average = sum / m_trajData.count();
}

namespace TrajUtills {

double generalBeginTime(const QList<Traj*> &trajs)
{
    double time = trajs.first()->getBeginTime();

    for (int i = 1; i < trajs.count(); i++) {
        if (trajs[i]->getBeginTime() < time) {
            time = trajs[i]->getBeginTime();
        }
    }

    return time;
}

double generalEndTime(const QList<Traj*> &trajs)
{
    double time = trajs.first()->getEndTime();

    for (int i = 1; i < trajs.count(); i++) {
        if (trajs[i]->getEndTime() > time) {
            time = trajs[i]->getEndTime();
        }
    }

    return time;
}

double generalTimeStep(const QList<Traj*> &trajs)
{
    double step = trajs.first()->getTimeStep();

    for (int i = 1; i < trajs.count(); i++) {
        if (trajs[i]->getTimeStep() < step) {
            step = trajs[i]->getTimeStep();
        }
    }

    return step;
}

} // TrajUtills

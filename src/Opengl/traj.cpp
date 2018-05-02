#include "traj.hpp"

Traj::Traj(QTextStream &stream, const Section &section)
    : m_section(section)
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

const QColor &Traj::getColor() const
{
    return m_color;
}

void Traj::setColor(const QColor &color)
{
    m_color = color;
    setData();
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

const QVector3D &Traj::getAverage() const
{
    return m_average;
}

const GLfloat *Traj::getConstData() const
{
    return m_data.constData();
}

void Traj::setSection(const Section &section)
{
    m_section = section;
}

void Traj::setData()
{
    /* Reset data */
    m_data.clear();
    int size = (m_trajData.count() - 1) * m_section.getCount() * 4 * 3;
    m_data.reserve(size);

    /* Create normals */
    QList<QVector3D> normals;
    for (int i = 1; i < m_trajData.count(); i++) {
        normals.push_back(m_trajData[i] - m_trajData[i - 1]);
    }

    /* Create sections */
    QList<Section> sections;
    for (int i = 0; i < normals.count(); i++) {
        m_section.setPlane(m_trajData[i], normals[i]);
        sections.push_back(m_section);
    }
    m_section.setPlane(m_trajData.last(), normals.last());
    sections.push_back(m_section);

    /* Create vectors */
    QList<QVector3D> vectors;
    for (int i = 1; i < sections.count(); i++) {
        for (int j = 1; j < sections[i].getCount(); j++) {
            vectors.push_back(sections[i][j]);
            vectors.push_back(sections[i][j - 1]);
            vectors.push_back(sections[i - 1][j - 1]);
            vectors.push_back(sections[i - 1][j]);
        }
        vectors.push_back(sections[i][0]);
        vectors.push_back(sections[i][sections[i].getCount() - 1]);
        vectors.push_back(sections[i - 1][sections[i].getCount() - 1]);
        vectors.push_back(sections[i - 1][0]);
    }

    /* Create final data */
    for (int i = 0; i < vectors.count(); i++) {
        m_data.push_back(vectors[i].x());
        m_data.push_back(vectors[i].y());
        m_data.push_back(vectors[i].z());
    }
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

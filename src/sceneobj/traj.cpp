#include "traj.hpp"

Traj::Traj(const QString &name, QTextStream &stream, const Section &section)
    : m_name(name),
      m_section(section),
      m_timeBorder(0),
      m_color(1.0, 1.0, 1.0),
      m_belowColor(1.0, 0.0, 0.0),
      m_aboveColor(1.0, 1.0, 1.0),
      m_isDisplayed(true),
      m_isCollisionMapped(false)
{
    addTimeAttributes(stream);
    addTrajVertices(stream);

    computeBufferData();
    computeBarycenter();
}

int Traj::getVertexCount() const
{
    return getVertexCount(m_timeEnd);
}

int Traj::getVertexCount(double time) const
{
    return (time - m_timeBegin) * m_valPerSec * m_section.getVertexCount() * 4;
}

int Traj::getSegmentCount() const
{
    return m_segments.count();
}

int Traj::getBufferSize() const
{
    return m_bufferData.count();
}

int Traj::getBufferSize(double time) const
{
    if (m_bufferData.empty()) {
        return 0;
    }
    else {
        return getVertexCount(time) * m_segments[0].getBufferSize();
    }
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
    m_color = Color(color.redF(), color.greenF(), color.blueF());
}

const Color &Traj::getColorVec() const
{
    return m_color;
}

const Color &Traj::getColorBelowTimeBorder() const
{
    return m_belowColor;
}

const Color &Traj::getColorAboveTimeBorder() const
{
    return m_aboveColor;
}

const QVector3D &Traj::getBarycenter() const
{
    return m_barycenter;
}

const QVector3D &Traj::getInitials() const
{
    return m_trajVertices.at(0);
}

QString Traj::getStringInitials() const
{
    QVector3D initials = getInitials();

    QString stringInitials;

    stringInitials.append('(');
        stringInitials.append(QString::number(initials.x()));
        stringInitials.append(',');
        stringInitials.append(QString::number(initials.y()));
        stringInitials.append(',');
        stringInitials.append(QString::number(initials.z()));
    stringInitials.append(')');

    return stringInitials;
}

int Traj::getTimeBorder() const
{
    return m_timeBorder;
}

void Traj::setTimeBorder(double time)
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

const GLfloat *Traj::getBufferData() const
{
    return m_bufferData.constData();
}

bool Traj::detectSegmentCollision(const Traj &t1, const Traj &t2, int segmentIndex)
{
    TrajSegment segment1 = t1.m_segments.at(segmentIndex);
    TrajSegment segment2 = t2.m_segments.at(segmentIndex);

    bool isCollided = TrajSegment::detectFullCollision(segment1, segment2);

    return isCollided;
}

void Traj::addTimeAttributes(QTextStream &stream)
{
    bool isAllConverted = true;
    bool isConverted;

    m_timeBegin = stream.readLine().toDouble(&isConverted);
    isAllConverted = isAllConverted && isConverted;

    m_timeEnd = stream.readLine().toDouble(&isConverted);
    isAllConverted = isAllConverted && isConverted;

    m_valPerSec = stream.readLine().toDouble(&isConverted);
    isAllConverted = isAllConverted && isConverted;

    if (!isAllConverted) {
        throw std::logic_error("");
    }
}

void Traj::addTrajVertices(QTextStream &stream)
{
    int numTrajVertices = (m_timeEnd - m_timeBegin) * m_valPerSec + 1;
    m_trajVertices.reserve(numTrajVertices);

    QStringList strVertex;
    QVector3D vec;
    while (!stream.atEnd()) {
        strVertex = stream.readLine().split(',');

        vec = {strVertex.at(0).toFloat(),
               strVertex.at(1).toFloat(),
               strVertex.at(2).toFloat()};
        m_trajVertices.push_back(vec);
    }
}

void Traj::computeBufferData()
{
    int size = 2 * (m_trajVertices.count() - 1) * m_section.getVertexCount() * 4 * 3;
    m_bufferData.reserve(size);

    Normal norm;

    /* Get initial data */
    if (m_trajVertices.count() >= 2) {
        norm = m_trajVertices[1] - m_trajVertices[0];
        m_section.setPlane(m_trajVertices[0], norm);
    }

    /* Get the rest data */
    for (int i = 2; i < m_trajVertices.count(); i++) {
        norm = m_trajVertices[i] - m_trajVertices[i - 1];

        Section prevSection = m_section;
        m_section.setPlane(m_trajVertices[i - 1], norm);

        TrajSegment segment(prevSection, m_section);
        m_segments.push_back(segment);
        segment.appendToBuffer(m_bufferData);
    }

    /* Get last data */
    Section prevSection = m_section;
    m_section.setPlane(m_trajVertices.last(), norm);
    TrajSegment segment(prevSection, m_section);
    m_segments.push_back(segment);
    segment.appendToBuffer(m_bufferData);
}

void Traj::computeBarycenter()
{
    QVector3D sum(0.0, 0.0, 0.0);
    for (int i = 0; i < m_trajVertices.count(); i++) {
        sum += m_trajVertices[i];
    }

    m_barycenter = sum / m_trajVertices.count();
}







namespace TrajUtills {

double computeGeneralBeginTime(const QList<Traj*> &trajs)
{
    double time = trajs.first()->getBeginTime();

    for (int i = 1; i < trajs.count(); i++) {
        if (trajs[i]->getBeginTime() < time) {
            time = trajs[i]->getBeginTime();
        }
    }

    return time;
}

double computeGeneralEndTime(const QList<Traj*> &trajs)
{
    double time = trajs.first()->getEndTime();

    for (int i = 1; i < trajs.count(); i++) {
        if (trajs[i]->getEndTime() > time) {
            time = trajs[i]->getEndTime();
        }
    }

    return time;
}

double computeGeneralTimeStep(const QList<Traj*> &trajs)
{
    double step = trajs.first()->getTimeStep();

    for (int i = 1; i < trajs.count(); i++) {
        if (trajs[i]->getTimeStep() < step) {
            step = trajs[i]->getTimeStep();
        }
    }

    return step;
}

int computeCollisionSegmentIndex(const QList<Traj *> &trajs)
{
    bool isCollided;
    int numSegments = trajs[0]->getSegmentCount();
    for (int i = 0; i < numSegments; i++) {
        for (int j = 0; j < trajs.count(); j++) {
            for (int k = j + 1; k < trajs.count(); k++) {
                isCollided = Traj::detectSegmentCollision(*trajs[j], *trajs[k], i);

                if(!isCollided) {
                    return i;
                }
            }
        }
    }

    return -1;
}

} // TrajUtills

#include "traj.hpp"

Traj::Traj(double timeBegin,
           double timeEnd,
           int pointPerSec,
           bool displayStatus,
           const QColor &color)
    : m_timeBegin(timeBegin),
      m_timeEnd(timeEnd),
      m_pointPerSec(pointPerSec),
      m_displayStatus(displayStatus),
      m_color(color)
{
}

const QVector3D &Traj::get(double time) const
{
    int pos = time * m_pointPerSec;

    return m_data.at(pos);
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
    return 1.0 / m_pointPerSec;
}

int Traj::getDataCount() const
{
    return 3 * getVertexCount();
}

int Traj::getDataCount(double time) const
{
    return 3 * getVertexCount(time);
}

int Traj::getVertexCount() const
{
    return m_data.count();
}

int Traj::getVertexCount(double time) const
{
    if (time < m_timeBegin) {
        time = m_timeBegin;
    }
    else if (time > m_timeEnd) {
        time = m_timeEnd;
    }

    return (time - m_timeBegin) * m_pointPerSec;
}

bool Traj::getDisplayStatus() const
{
    return m_displayStatus;
}

void Traj::setDisplayStatus(bool status)
{
    m_displayStatus = status;
}

void Traj::setDisplayStatus(Qt::CheckState state)
{
    if (state == Qt::Checked) {
        m_displayStatus = true;
    }
    else {
        m_displayStatus = false;
    }
}

const QColor &Traj::getColor() const
{
    return m_color;
}

void Traj::setColor(const QColor &color)
{
    m_color = color;
}

const QVector3D &Traj::getInitials() const
{
    return m_data.first();
}

QVector3D Traj::getAverage() const
{
    double sx = 0, sy = 0, sz = 0;
    for (auto it = m_data.constBegin(); it != m_data.constEnd(); ++it) {
        sx += (*it).x();
        sy += (*it).y();
        sz += (*it).z();
    }

    return QVector3D(sx / m_data.count(),
                     sy / m_data.count(),
                     sz / m_data.count());
}

GLfloat *Traj::getOpenglData() const
{
    GLfloat *openglData = new GLfloat[getDataCount()];

    int i = 0;
    for (auto it = m_data.constBegin(); it != m_data.constEnd(); ++it) {
        openglData[i++] = (*it).x();
        openglData[i++] = (*it).y();
        openglData[i++] = (*it).z();
    }

    return openglData;
}

void Traj::add(float x, float y, float z)
{
    m_data.push_back(QVector3D(x, y, z));
}

Traj *TrajUtills::readTraj(const QString &path)
{
    QFile file(path);
    if (!file.exists()) {
        qDebug() << "Cannot find " << file.fileName();
    }

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);

        /* Read traj info */
        double timeBegin = stream.readLine().toDouble();
        double timeEnd = stream.readLine().toDouble();
        double pointsPerSec = stream.readLine().toDouble();

        /* Read and set traj data */
        Traj *traj = new Traj(timeBegin, timeEnd, pointsPerSec);

        QStringList values;
        while (!stream.atEnd()) {
            values = stream.readLine().split(',');

            traj->add(values.at(0).toFloat(),
                      values.at(1).toFloat(),
                      values.at(2).toFloat());
        }

        file.close();

        if (stream.status() == QTextStream::Ok) {
            qDebug() << "The trajectory was successfully loaded from " << file.fileName();

            return traj;
        }
        else {
            qDebug() << "The tracjection was not loaded from" << file.fileName();
        }
    }
    else {
        qDebug() << "Cannot load trajectory from " << file.fileName();
    }

    return nullptr;
}

double TrajUtills::minimumBeginTime(const QList<Traj*> &trajList)
{
    double min = trajList.first()->getBeginTime();

    double time;
    for (auto it = trajList.constBegin(); it != trajList.constEnd(); ++it) {
        time = (*it)->getBeginTime();
        if (time < min) {
            min = time;
        }
    }

    return min;
}

double TrajUtills::maximumEndTime(const QList<Traj*> &trajList)
{
    double max = trajList.first()->getEndTime();

    double time;
    for (auto it = trajList.constBegin(); it != trajList.constEnd(); ++it) {
        time = (*it)->getEndTime();
        if (time > max) {
            max = time;
        }
    }

    return max;
}

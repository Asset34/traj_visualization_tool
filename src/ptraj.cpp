#include "ptraj.hpp"

PTraj::PTraj(QFile *file, int timeStep)
    : TIME_STEP(timeStep)
{
    if (!file->exists()) {
        qDebug() << "Cannot find " << file->fileName();
    }

    if (file->open(QIODevice::ReadOnly)) {
        QTextStream stream(file);

        /* Load tracjectory data from file */
        QString line;
        QStringList values;
        State state;
        while (!stream.atEnd()) {
            line = stream.readLine();
            values = line.split(',');

            state = {values.at(0).toDouble(),
                     values.at(1).toDouble(),
                     values.at(2).toDouble()};

            m_states.push_back(state);
        }

        /* Stream debug info */
        if (stream.status() == QTextStream::Ok) {
            qDebug() << "The trajectory was successfully loaded from " << file->fileName();
        }
        else {
            qDebug() << "The tracjection was not loaded from" << file->fileName();
        }

        file->close();
    }
    else {
        qDebug() << "Cannot load trajectory from " << file->fileName();
    }
}

const State &PTraj::at(int pos) const
{
    return m_states[pos];
}

const State &PTraj::atTime(double time) const
{
    return at(timeToPos(time));
}

QList<State>::const_iterator PTraj::getBeginIterator() const
{
    return m_states.constBegin();
}

QList<State>::const_iterator PTraj::getEndIterator() const
{
    return m_states.constEnd();
}

int PTraj::timeToPos(double time) const
{
    return time / TIME_STEP;
}

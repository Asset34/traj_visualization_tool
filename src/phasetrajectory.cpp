#include "phasetrajectory.hpp"

PhaseTrajectory::PhaseTrajectory(QFile *file)
{
    if (file->open(QIODevice::ReadOnly)) {
        QTextStream stream(file);

        QString line;
        QStringList values;
        State state;
        while (!stream.atEnd()) {
            /* Get numbers from line */
            line = stream.readLine();
            values = line.split(',');

            /* Convert to state */
            state = {values.at(0).toDouble(),
                     values.at(1).toDouble(),
                     values.at(2).toDouble()};

            m_states.push_back(state);
        }

        if (stream.status() == QTextStream::Ok) {
            qDebug() << "The trajectory was successfully loaded from " << file->fileName();
        }

        file->close();
    }
    else {
        qDebug() << "Cannot load trajectory from " << file->fileName();
    }
}

const State &PhaseTrajectory::at(int pos) const
{
    return m_states.at(pos);
}

const State &PhaseTrajectory::atTime(double time) const
{
    return at(timeToPos(time));
}

QList<State>::const_iterator PhaseTrajectory::getIterator() const
{
    return m_states.constBegin();
}

int PhaseTrajectory::timeToPos(double time) const
{
    return time / TIME_STEP;
}

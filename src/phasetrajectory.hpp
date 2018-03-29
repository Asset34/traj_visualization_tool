#ifndef PHASETRAJECTORY_HPP
#define PHASETRAJECTORY_HPP

#include <QList>
#include <QTextStream>
#include <QStringList>
#include <QString>

#include <QDebug>

struct State
{
    double x1;
    double x2;
    double x3;
};

class PhaseTrajectory
{
public:
    explicit PhaseTrajectory(QFile *file);

    const State &at(int pos) const;
    const State &atTime(double time) const;

    QList<State>::const_iterator getIterator() const;

private:
    int timeToPos(double time) const;

    QList<State> m_states;

    const double TIME_STEP = 0.01;
};

#endif // PHASETRAJECTORY_HPP

#ifndef PTRAJ_HPP
#define PTRAJ_HPP

#include <QList>
#include <QString>
#include <QTextStream>
#include <QStringList>

#include <QDebug>

struct State
{
    double x1;
    double x2;
    double x3;
};

class PTraj
{
public:
    explicit PTraj(QFile *file, int timeStep);

    const State &at(int pos) const;
    const State &atTime(double time) const;

    QList<State>::const_iterator getBeginIterator() const;
    QList<State>::const_iterator getEndIterator() const;

private:
    int timeToPos(double time) const;

    QList<State> m_states;
    const double TIME_STEP;
};

#endif // PTRAJ_HPP

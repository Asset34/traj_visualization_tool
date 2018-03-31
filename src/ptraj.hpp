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

struct PMetaTraj
{
    QString dataPath;
    int timeStep;
};

class PTraj
{
public:
    explicit PTraj(int timeStep);

    const State &at(int pos) const;
    const State &atTime(double time) const;
    void add(const State &state);

    QList<State>::const_iterator getBeginIterator() const;
    QList<State>::const_iterator getEndIterator() const;

private:
    const double TIME_STEP;

    QList<State> m_states;

    int timeToPos(double time) const;
};

#endif // PTRAJ_HPP

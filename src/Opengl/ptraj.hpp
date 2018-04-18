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

struct PTrajMeta
{
    QString dataPath;
    int timeStep;
};

class PTraj
{
public:
    const State &at(int pos) const;

    void add(const State &state);

    QList<State>::const_iterator getBIterator() const;
    QList<State>::const_iterator getEIterator() const;

private:
    QList<State> m_states;
};

#endif // PTRAJ_HPP

#include "ptraj.hpp"

PTraj::PTraj(int timeStep)
    : TIME_STEP(timeStep)
{
}

const State &PTraj::at(int pos) const
{
    return m_states[pos];
}

const State &PTraj::atTime(double time) const
{
    return at(timeToPos(time));
}

void PTraj::add(const State &state)
{
    m_states.push_back(state);
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

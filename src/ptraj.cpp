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

QList<State>::const_iterator PTraj::getBIterator() const
{
    return m_states.constBegin();
}

QList<State>::const_iterator PTraj::getEIterator() const
{
    return m_states.constEnd();
}

QList<State>::const_iterator PTraj::getIterator(double time) const
{
    // Need to test it
    return m_states.constBegin() + timeToPos(time);
}

int PTraj::timeToPos(double time) const
{
    return time / TIME_STEP;
}

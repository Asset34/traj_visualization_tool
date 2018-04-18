#include "ptraj.hpp"

const State &PTraj::at(int pos) const
{
    return m_states[pos];
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

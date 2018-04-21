#include "ptraj.hpp"

GLfloat *PTraj::getOpenglData() const
{
    GLfloat *openglData = new GLfloat[m_data.count() * N_COORD];

    int i = 0;
    for (auto it = m_data.constBegin(); it != m_data.constEnd(); ++it) {
        openglData[i++] = (*it).x();
        openglData[i++] = (*it).y();
        openglData[i++] = (*it).z();
    }

    return openglData;
}

int PTraj::getDataCount() const
{
    return getVertexCount() * N_COORD;
}

int PTraj::getDataCount(int time) const
{
    return getVertexCount(time) * N_COORD;
}

int PTraj::getVertexCount() const
{
    return m_data.count();
}

int PTraj::getVertexCount(int time) const
{
    return float(time) / TIME_STEP;
}

const State &PTraj::getInitials() const
{
    return m_data.first();
}

void PTraj::add(const State &state)
{
    m_data.push_back(state);
}

void PTraj::add(float x, float y, float z)
{
    add(State(x, y, z));
}

#ifndef PTRAJ_HPP
#define PTRAJ_HPP

#include <QVector3D>
#include <QList>

#include "qopengl.h"

typedef QVector3D State;

class PTraj
{

public:
    GLfloat *getOpenglData() const;

    int getDataCount() const;
    int getDataCount(int time) const;
    int getVertexCount() const;
    int getVertexCount(int time) const;

    const State &getInitials() const;

    void add(const State &state);
    void add(float x, float y, float z);

private:
    const int N_COORD     =    3;
    const float TIME_STEP = 0.01;

    QList<State> m_data;

};

#endif // PTRAJ_HPP

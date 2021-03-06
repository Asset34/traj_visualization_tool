#ifndef TRAJBUFFER_HPP
#define TRAJBUFFER_HPP

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include <QVector3D>

#include "../sceneobj/traj.hpp"

class TrajBuffer : protected QOpenGLFunctions
{
public:
    explicit TrajBuffer(Traj *traj);
    ~TrajBuffer();

    void bind();
    void release();

    const Color &getColor() const;
    const Color &getBelowColor() const;
    const Color &getAboveColor() const;

    int getTimeBorder() const;

    int getVertexCount(double time) const;

    bool isDisplayed() const;
    bool isSeparated() const;

private:
    Traj *m_traj;
    QOpenGLBuffer m_vbo;
    QOpenGLVertexArrayObject m_vao;
};

#endif // TRAJBUFFER_HPP

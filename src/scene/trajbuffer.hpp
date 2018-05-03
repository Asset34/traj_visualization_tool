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

    QVector3D getColor() const;
    int getVertexCount() const;
    int getVertexCount(double time) const;
    bool getDisplayStatus() const;

private:
    Traj *m_traj;
    QOpenGLBuffer m_vbo;
    QOpenGLVertexArrayObject m_vao;
};

#endif // TRAJBUFFER_HPP

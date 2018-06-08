#include "trajbuffer.hpp"

TrajBuffer::TrajBuffer(Traj *traj)
    : m_traj(traj)
{
    initializeOpenGLFunctions();

    /* Create VAO with VBO */
    m_vao.create();
    m_vao.bind();
        m_vbo.create();
        m_vbo.bind();
        m_vbo.allocate(traj->getBufferData(), traj->getBufferSize() * sizeof(GLfloat));
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
    m_vao.release();
}

TrajBuffer::~TrajBuffer()
{
    delete m_traj;

    m_vbo.destroy();
    m_vao.destroy();
}

void TrajBuffer::bind()
{
    m_vao.bind();
}

void TrajBuffer::release()
{
    m_vao.release();
}

const Color &TrajBuffer::getColor() const
{
    return m_traj->getColorVec();
}

const Color &TrajBuffer::getBelowColor() const
{
    return m_traj->getColorBelowTimeBorder();
}

const Color &TrajBuffer::getAboveColor() const
{
    return m_traj->getColorAboveTimeBorder();
}

int TrajBuffer::getTimeBorder() const
{
    return m_traj->getTimeBorder();
}

int TrajBuffer::getVertexCount(double time) const
{
    return m_traj->getVertexCount(time);
}

bool TrajBuffer::isDisplayed() const
{
    return m_traj->isDisplayed();
}

bool TrajBuffer::isSeparated() const
{
    return m_traj->isCollisionMapped();
}

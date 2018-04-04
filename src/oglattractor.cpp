#include "oglattractor.hpp"

OGLAttractor::OGLAttractor(QWidget *parent)
    : QGLWidget(parent),
      m_ptraj(nullptr)
{
}

OGLAttractor::~OGLAttractor()
{
    delete m_ptraj;
}

void OGLAttractor::drawTraj()
{
    glBegin(GL_LINE_STRIP);
        qglColor(Qt::white);
        for (auto it = m_ptraj->getBIterator(); it != m_ptraj->getEIterator(); ++it) {
            drawState(it);
        }
        glEnd();
}

void OGLAttractor::drawState(const QList<State>::const_iterator &it)
{
    glVertex3d((*it).x1, (*it).x2, (*it).x3);
}

void OGLAttractor::initializeGL()
{
    qglClearColor(Qt::black);
}

void OGLAttractor::resizeGL(int w, int h)
{
    glViewport(0, 0, GLint(w), GLint(h));
}

void OGLAttractor::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawTraj();
}

void OGLAttractor::slotAddTraj(PTraj *ptraj)
{
    delete m_ptraj;

    m_ptraj = ptraj;
}

#ifndef OGLATTRACTOR_HPP
#define OGLATTRACTOR_HPP

#include <QGLWidget>
#include <QPair>

#include "ptraj.hpp"

/*
 * TODO: Store trajectories as smart pointers
 * (because copy PTraj is too expensive)
 */
class OGLAttractor : public QGLWidget
{
    Q_OBJECT

public:
    explicit OGLAttractor(QWidget *parent = nullptr);
    ~OGLAttractor();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

private:
    PTraj *m_ptraj;

    void drawTraj();
    void drawState(const QList<State>::const_iterator &it);

public slots:
    void slotAddTraj(PTraj *ptraj);
};

#endif // OGLATTRACTOR_HPP

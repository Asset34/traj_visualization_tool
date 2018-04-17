#ifndef OGLATTRACTOR_HPP
#define OGLATTRACTOR_HPP

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include <QMatrix4x4>

#include <QMouseEvent>
#include <QPoint>

#include <QDebug>

/*
 * TODO: Store trajectories as smart pointers
 * (because copy PTraj is too expensive and
 *  store PTraj as pointer is too unsafe)
 */
class OGLAttractor : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit OGLAttractor(QWidget *parent = nullptr);
    ~OGLAttractor();

protected:

    /* OpenGL events */
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    /* Mouse events */
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private:
    /* matrixes */
    QMatrix4x4 m_model;

    /* Locations */
    int m_transformLoc;

    /* OpenGL objects */
    QOpenGLBuffer m_vbo;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLShaderProgram *m_shprogram;

    /* Data */
    GLfloat *vertices;
};

#endif // OGLATTRACTOR_HPP

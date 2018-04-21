#ifndef OGLATTRACTOR_HPP
#define OGLATTRACTOR_HPP

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

#include <QPoint>
#include <QMatrix4x4>

#include <QMouseEvent>

#include <QDebug>

#include "camera.hpp"
#include "ptraj.hpp"

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

    void addTraj(PTraj *ptraj);

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
    constexpr static const GLfloat XRANGLE_OFFSET = 180.0;
    constexpr static const GLfloat YRANGLE_OFFSET = 180.0;
    constexpr static const float YFOV             =  45.0;
    constexpr static const float ZNEAR            =  0.01;
    constexpr static const float ZFAR             = 100.0;

    Camera m_camera;
    QPoint m_mousePos;

    /* matrixes */
    QMatrix4x4 m_model;
    QMatrix4x4 m_proj;

    /* Locations */
    int m_transformLoc;
    int m_colorLoc;

    /* OpenGL objects */
    QOpenGLBuffer m_vbo;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLShaderProgram *m_shprogram;

    /* Data */
    GLfloat *vertices;

};

#endif // OGLATTRACTOR_HPP

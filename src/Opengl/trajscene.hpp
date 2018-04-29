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
#include "traj.hpp"

class TrajBuffer : protected QOpenGLFunctions
{
public:
    explicit TrajBuffer(Traj *traj);
    ~TrajBuffer();

    void bind();
    void release();

    Traj *getTraj() const;

    QVector3D getColor() const;
    int getVertexCount() const;
    int getVertexCount(double time) const;
    bool getDisplayStatus() const;

private:
    Traj *m_traj;
    QOpenGLBuffer m_vbo;
    QOpenGLVertexArrayObject m_vao;

    GLfloat *m_sceneData;
};



class TrajScene : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit TrajScene(QWidget *parent = nullptr);
    ~TrajScene();

public slots:
    void addTraj(Traj *traj);
    void deleteTraj(int pos);
    void focusTraj(Traj *traj);
    void setCurrentTime(double time);

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
    constexpr static const float YFOV             =   45.0;
    constexpr static const float ZNEAR            =   0.01;
    constexpr static const float ZFAR             = 1000.0;
    constexpr static const float YAW_SENS         =    0.4;
    constexpr static const float PITCH_SENS       =    0.4;
    constexpr static const float ZOOMUP_FACTOR    =    0.9;
    constexpr static const float ZOOMDOWN_FACTOR  =    1.1;

    double m_currentTime;

    Camera m_camera;
    QPoint m_mousePos;

    QOpenGLShaderProgram m_shprogram;

    /* Matrixes */
    QMatrix4x4 m_model;
    QMatrix4x4 m_proj;

    /* Locations */
    int m_transformLoc;
    int m_colorLoc;

    /* Data buffers */
    QList<TrajBuffer*> m_trajBuffers;
};

#endif // OGLATTRACTOR_HPP

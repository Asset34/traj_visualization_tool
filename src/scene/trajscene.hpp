#ifndef OGLATTRACTOR_HPP
#define OGLATTRACTOR_HPP

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <QPoint>
#include <QMatrix4x4>

#include <QMouseEvent>

#include <QDebug>

#include "camera.hpp"
#include "trajbuffer.hpp"

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

    void setBackgroundColor(const QColor &color);

    void setLightAmbientStrength(double strength);
    void setLightColor(const QColor &color);
    void setLightSourcePosition(const QVector3D &vec);

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

    QColor m_backgroundColor;

    QVector3D m_lightColor;
    float m_lightAmbientStrength;
    QVector3D m_lightSourcePos;

    Camera m_camera;
    QPoint m_mousePos;

    QOpenGLShaderProgram m_shprogram;

    /* Matrixes */
    QMatrix4x4 m_model;
    QMatrix4x4 m_proj;

    /* Locations */
    int m_modelLoc;
    int m_viewLoc;
    int m_projectionLoc;
    int m_objectColorLoc;
    int m_lightColorLoc;
    int m_lightPosLoc;
    int m_lightAmbientStrengthLoc;
    int m_viewPosLoc;

    /* Data buffers */
    QList<TrajBuffer*> m_buffers;
};

#endif // OGLATTRACTOR_HPP

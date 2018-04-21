#include "oglattractor.hpp"

OGLAttractor::OGLAttractor(QWidget *parent)
    : QOpenGLWidget(parent),
      m_shprogram(nullptr),
      vertices(nullptr)
{
    /* Set antialiasing and vsync for Opengl */
    QSurfaceFormat fmt;
    fmt.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(fmt);
}

OGLAttractor::~OGLAttractor()
{
    if (!m_shprogram) {
        return;
    }

    makeCurrent();
    m_vbo.destroy();
    m_shprogram = nullptr;
    doneCurrent();

    delete vertices;
}

void OGLAttractor::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0);

    vertices = new GLfloat[108]{
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    /* Create shader program */
    m_shprogram = new QOpenGLShaderProgram;
    m_shprogram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl");
    m_shprogram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl");
    m_shprogram->bindAttributeLocation("position", 0);
    m_shprogram->link();

    /* Get locations */
    m_shprogram->bind();
        m_transformLoc = m_shprogram->uniformLocation("transform");
        m_colorLoc = m_shprogram->uniformLocation("color");
    m_shprogram->release();

    /* Create VAO with VBOs */
    m_vao.create();
    m_vao.bind();
        m_vbo.create();
        m_vbo.bind();
        m_vbo.allocate(vertices, 108 * sizeof(GLfloat));

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(0);

    m_vao.release();
}

void OGLAttractor::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(YFOV, float(w) / h, ZNEAR, ZFAR);
}

void OGLAttractor::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    /* Configure model matrixes */
    m_model.setToIdentity();

    /* Draw */
    m_shprogram->bind();
        m_shprogram->setUniformValue(m_transformLoc, m_proj * m_camera.getViewMatrix() *  m_model);
        m_vao.bind();
            m_shprogram->setUniformValue(m_colorLoc, QVector3D(1.0, 0.0, 0.0));
            glDrawArrays(GL_TRIANGLES, 0, 6);
            m_shprogram->setUniformValue(m_colorLoc, QVector3D(1.0, 1.0, 1.0));
            glDrawArrays(GL_TRIANGLES, 6, 6);
            m_shprogram->setUniformValue(m_colorLoc, QVector3D(0.0, 1.0, 0.0));
            glDrawArrays(GL_TRIANGLES, 12, 6);
            m_shprogram->setUniformValue(m_colorLoc, QVector3D(0.0, 0.0, 1.0));
            glDrawArrays(GL_TRIANGLES, 18, 6);
            m_shprogram->setUniformValue(m_colorLoc, QVector3D(1.0, 1.0, 0.0));
            glDrawArrays(GL_TRIANGLES, 24, 6);
            m_shprogram->setUniformValue(m_colorLoc, QVector3D(1.0, 0.0, 1.0));
            glDrawArrays(GL_TRIANGLES, 30, 6);
        m_vao.release();
    m_shprogram->release();
}

void OGLAttractor::mousePressEvent(QMouseEvent *event)
{
    m_mousePos = event->pos();
}

void OGLAttractor::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::RightButton)) {
        float dyaw = YAW_SENS * (m_mousePos.x() - event->pos().x());
        float dpitch = PITCH_SENS * (event->pos().y() - m_mousePos.y());

        m_camera.rotate(dyaw, dpitch);

        m_mousePos = event->pos();
        update();
    }
}

void OGLAttractor::wheelEvent(QWheelEvent *event)
{
    int numSteps = event->delta();

    if (numSteps > 0) {
        m_camera.zoom(ZOOMUP_FACTOR);
    }
    else {
        m_camera.zoom(ZOOMDOWN_FACTOR);
    }

    update();
}

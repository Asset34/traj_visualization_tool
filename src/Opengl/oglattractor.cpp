#include "oglattractor.hpp"

OGLAttractor::OGLAttractor(QWidget *parent)
    : QOpenGLWidget(parent),
      m_shprogram(nullptr),
      vertices(nullptr)
{
    // To avoid the flicker when resizing window
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

    vertices = new GLfloat[9]{
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
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
    m_shprogram->release();

    /* Create VAO with VBOs */
    m_vao.create();
    m_vao.bind();
        m_vbo.create();
        m_vbo.bind();
        m_vbo.allocate(vertices, 9 * sizeof(GLfloat));

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(0);

    m_vao.release();
}

void OGLAttractor::resizeGL(int w, int h)
{

}

void OGLAttractor::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    /* Configure matrixes */
    m_model.setToIdentity();

    /* Draw */
    m_shprogram->bind();
        m_shprogram->setUniformValue(m_transformLoc, m_model);
        m_vao.bind();
            glDrawArrays(GL_TRIANGLES, 0, 9);
        m_vao.release();
    m_shprogram->release();
}

void OGLAttractor::mousePressEvent(QMouseEvent *event)
{

}

void OGLAttractor::mouseMoveEvent(QMouseEvent *event)
{

}

void OGLAttractor::wheelEvent(QWheelEvent *event)
{

}

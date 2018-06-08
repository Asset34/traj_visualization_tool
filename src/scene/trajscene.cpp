#include "trajscene.hpp"

TrajScene::TrajScene(QWidget *parent)
    : QOpenGLWidget(parent)
{
    /* Set vsync */
    QSurfaceFormat fmt;
    fmt.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(fmt);
}

TrajScene::~TrajScene()
{
    for (int i = 0; i < m_buffers.count(); i++) {
        delete m_buffers[i];
    }
}

void TrajScene::addTraj(Traj *traj)
{
    makeCurrent();
    m_buffers.push_back(new TrajBuffer(traj));
    update();
}

void TrajScene::deleteTraj(int pos)
{
    m_buffers.removeAt(pos);
    update();
}

void TrajScene::focusTraj(Traj *traj)
{
    m_camera.moveCenter(traj->getBarycenter());
    update();
}

void TrajScene::setCurrentTime(double time)
{
    m_currentTime = time;
    update();
}

void TrajScene::setBackgroundColor(const QColor &color)
{
    makeCurrent();

    m_backgroundColor = color;

    glClearColor(color.redF() * m_lightAmbientStrength,
                 color.greenF() * m_lightAmbientStrength,
                 color.blueF() * m_lightAmbientStrength,
                 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    update();
}

void TrajScene::setLightAmbientStrength(double strength)
{
    m_lightAmbientStrength = strength;
    setBackgroundColor(m_backgroundColor);
    update();
}

void TrajScene::setLightColor(const QColor &color)
{
    m_lightColor.setX(color.redF());
    m_lightColor.setY(color.greenF());
    m_lightColor.setZ(color.blueF());

    update();
}

void TrajScene::setLightSourcePosition(const QVector3D &vec)
{
    m_lightSourcePos = vec;
    update();
}

void TrajScene::initializeGL()
{
    initializeOpenGLFunctions();

    /* Set default values */
    setBackgroundColor(Qt::white);
    setLightAmbientStrength(0.2);
    setLightColor(Qt::white);
    setLightSourcePosition({0.0, 0.0, 10.0});

    /* Create shader program */
    m_shprogram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex_shader.glsl");
    m_shprogram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");
    m_shprogram.bindAttributeLocation("pos", 0);
    m_shprogram.bindAttributeLocation("normal", 1);
    m_shprogram.link();

    /* Get locations */
    m_shprogram.bind();
        m_modelLoc = m_shprogram.uniformLocation("model");
        m_viewLoc = m_shprogram.uniformLocation("view");
        m_projectionLoc = m_shprogram.uniformLocation("projection");
        m_objectColorLoc = m_shprogram.uniformLocation("objectColor");
        m_lightColorLoc = m_shprogram.uniformLocation("lightColor");
        m_lightPosLoc = m_shprogram.uniformLocation("lightPos");
        m_lightAmbientStrengthLoc = m_shprogram.uniformLocation("lightAmbientStrength");
        m_viewPosLoc = m_shprogram.uniformLocation("viewPos");
    m_shprogram.release();
}

void TrajScene::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(YFOV, float(w) / h, ZNEAR, ZFAR);
}

void TrajScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    /* Configure scene matrixes */
    m_model.setToIdentity();

    /* Draw scene */
    m_shprogram.bind();   
        m_shprogram.setUniformValue(m_modelLoc, m_model);
        m_shprogram.setUniformValue(m_viewLoc, m_camera.getViewMatrix());
        m_shprogram.setUniformValue(m_projectionLoc, m_proj);
        m_shprogram.setUniformValue(m_lightColorLoc, m_lightColor);
        m_shprogram.setUniformValue(m_lightPosLoc, m_lightSourcePos);
        m_shprogram.setUniformValue(m_lightAmbientStrengthLoc, m_lightAmbientStrength);
        m_shprogram.setUniformValue(m_viewPosLoc, m_camera.getPosition());

        for (int i = 0; i < m_buffers.count(); i++) {
            if (m_buffers[i]->isDisplayed()) {
                m_buffers[i]->bind();

                    if (m_buffers[i]->isSeparated()) {
                        double timeBorder = m_buffers[i]->getTimeBorder();

                        if (m_currentTime < timeBorder) {
                            m_shprogram.setUniformValue(m_objectColorLoc, m_buffers[i]->getBelowColor());
                            glDrawArrays(GL_QUADS, 0, m_buffers[i]->getVertexCount(m_currentTime));
                        }
                        else {
                            // Draw below part

                            m_shprogram.setUniformValue(m_objectColorLoc, m_buffers[i]->getBelowColor());
                            glDrawArrays(GL_QUADS, 0, m_buffers[i]->getVertexCount(timeBorder));

                            // Draw above aprt

                            int start = m_buffers[i]->getVertexCount(timeBorder);
                            int length = m_buffers[i]->getVertexCount(m_currentTime) - start;

                            m_shprogram.setUniformValue(m_objectColorLoc, m_buffers[i]->getAboveColor());
                            glDrawArrays(GL_QUADS, start, length);
                        }
                    }
                    else {
                        m_shprogram.setUniformValue(m_objectColorLoc, m_buffers[i]->getColor());
                        glDrawArrays(GL_QUADS, 0, m_buffers[i]->getVertexCount(m_currentTime));
                    }

                m_buffers[i]->release();
            }
        }

    m_shprogram.release();
}

void TrajScene::mousePressEvent(QMouseEvent *event)
{
    m_mousePos = event->pos();
}

void TrajScene::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::RightButton)) {
        float dyaw = YAW_SENS * (m_mousePos.x() - event->pos().x());
        float dpitch = PITCH_SENS * (event->pos().y() - m_mousePos.y());
        m_camera.rotate(dyaw, dpitch);

        m_mousePos = event->pos();

        update();
    }
}

void TrajScene::wheelEvent(QWheelEvent *event)
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

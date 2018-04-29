#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    /* Set antialiasing */
    QSurfaceFormat fmt;
    fmt.setSamples(10);
    QSurfaceFormat::setDefaultFormat(fmt);

    /* Configurate scene */
    m_scene = new TrajScene;

    /* Configurate time box */
    m_timeBox = new DoubleValueSlideBox("Time", 3, 0.1);
    m_timeBox->setEnabled(false);

    /* Configurate traj panel */
    m_trajPanel = new TrajPanel;

    /* Configurate scene layout */
    m_sceneLayout = new QVBoxLayout;
    m_sceneLayout->addWidget(m_scene);
    m_sceneLayout->addWidget(m_timeBox);

    /* Configurate panel layout */
    m_panelLayout = new QVBoxLayout;
    m_panelLayout->addWidget(m_trajPanel);

    /* Configurate main layout */
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->addLayout(m_sceneLayout);
    m_mainLayout->addLayout(m_panelLayout);

    /* Configure window */
    setWindowTitle("Attractor Visualizer");
    setLayout(m_mainLayout);
    resize(800, 500);

    /* Set connections */
    connect(m_trajPanel, &TrajPanel::trajAdded, m_scene, &TrajScene::addTraj);
    connect(m_trajPanel, &TrajPanel::trajDeleted, m_scene, &TrajScene::deleteTraj);
    connect(m_trajPanel, &TrajPanel::trajEdited, m_scene, static_cast<void (TrajScene::*)()>(&TrajScene::update));
    connect(m_trajPanel, &TrajPanel::trajFocused, m_scene, &TrajScene::focusTraj);
    connect(m_trajPanel, &TrajPanel::trajDisplayStatusChanged, m_scene, static_cast<void (TrajScene::*)()>(&TrajScene::update));
    connect(m_trajPanel, &TrajPanel::trajMinBeginTimeChanged, m_timeBox, &DoubleValueSlideBox::setMinimum);
    connect(m_trajPanel, &TrajPanel::trajMaxEndTimeChanged, m_timeBox, &DoubleValueSlideBox::setMaximum);
    connect(m_trajPanel, &TrajPanel::trajMaxEndTimeChanged, m_timeBox, &DoubleValueSlideBox::setValue);
    connect(m_trajPanel, &TrajPanel::trajMinTimeStepChanged, m_timeBox, &DoubleValueSlideBox::setStep);
    connect(m_trajPanel, &TrajPanel::trajStatusChanged, m_timeBox, &DoubleValueSlideBox::setEnabled);
    connect(m_timeBox, &DoubleValueSlideBox::valueChanged, m_scene, &TrajScene::setCurrentTime);
}

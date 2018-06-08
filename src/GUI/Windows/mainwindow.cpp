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
    m_scene->setLightColor(Qt::white);
    m_scene->setLightSourcePosition({0.0, 0.0, 1.0});

    /* Configurate time box */
    m_timeBox = new DoubleValueSlideBox("Time", 3, 0.1);
    m_timeBox->disable();

    /* Configurate traj control panel */
    m_trajControlPanel = new TrajControlPanel;

    /* Configurate traj panel */
    m_trajPanel = new TrajPanel;
    m_trajPanel->disable();

    /* Configurate scene panel */
    m_scenePanel = new ScenePanel;

    /* Configurate light panel */
    m_lightPanel = new LightPanel;

    /* Configurate scene layout */
    m_sceneLayout = new QVBoxLayout;
    m_sceneLayout->setMargin(0);
    m_sceneLayout->addWidget(m_scene);
    m_sceneLayout->addWidget(m_timeBox);

    /* Configurate panel layout */
    m_panelLayout = new QVBoxLayout;
    m_panelLayout->setMargin(0);
    m_panelLayout->addWidget(m_trajControlPanel);
    m_panelLayout->addWidget(m_trajPanel);
    m_panelLayout->addWidget(m_scenePanel);
    m_panelLayout->addWidget(m_lightPanel);

    /* Configurate panel scroll widget */
    m_panelScrollWidget = new QWidget;
    m_panelScrollWidget->setLayout(m_panelLayout);

    /* Configurate panel scroll area */
    m_panelScrollArea = new QScrollArea;
    m_panelScrollArea->setWidget(m_panelScrollWidget);
    m_panelScrollArea->setWidgetResizable(false);
    m_panelScrollArea->setFrameShape(QFrame::NoFrame);
    m_panelScrollArea->setFixedWidth(220);

    /* Configurate main layout */
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->addLayout(m_sceneLayout);
    m_mainLayout->addWidget(m_panelScrollArea);

    /* Configure window */
    setWindowTitle("Visualization tool");
    setContentsMargins(5, 15, 5, 5);
    setLayout(m_mainLayout);
    resize(1000, 600);

    /* Set connections */
    connect(m_trajControlPanel, &TrajControlPanel::trajAdded, m_scene, &TrajScene::addTraj);
    connect(m_trajControlPanel, &TrajControlPanel::trajDeleted, m_scene, &TrajScene::deleteTraj);
    connect(m_trajControlPanel, &TrajControlPanel::trajFocused, m_scene, &TrajScene::focusTraj);
    connect(m_trajControlPanel, &TrajControlPanel::trajUpdated, m_scene, static_cast<void (TrajScene::*)()>(&TrajScene::update));
    connect(m_trajControlPanel, &TrajControlPanel::generalBeginTimeChanged, m_timeBox, &DoubleValueSlideBox::setMinimum);
    connect(m_trajControlPanel, &TrajControlPanel::generalEndTimeChanged, m_timeBox, &DoubleValueSlideBox::setMaximum);
    connect(m_trajControlPanel, &TrajControlPanel::generalEndTimeChanged, m_timeBox, &DoubleValueSlideBox::setValue);
    connect(m_trajControlPanel, &TrajControlPanel::generalTimeStepChanged, m_timeBox, &DoubleValueSlideBox::setStep);
    connect(m_trajControlPanel, &TrajControlPanel::firstTrajWasAdded, m_timeBox, &DoubleValueSlideBox::enable);
    connect(m_trajControlPanel, &TrajControlPanel::lastTrajWasDeleted, m_timeBox, &DoubleValueSlideBox::disable);
    connect(m_trajControlPanel, &TrajControlPanel::trajSelected, m_trajPanel, &TrajPanel::setTraj);
    connect(m_trajControlPanel, &TrajControlPanel::firstTrajWasAdded, m_trajPanel, &TrajPanel::enable);
    connect(m_trajControlPanel, &TrajControlPanel::lastTrajWasDeleted, m_trajPanel, &TrajPanel::disable);
    connect(m_trajPanel, &TrajPanel::trajUpdated, m_scene, static_cast<void (TrajScene::*)()>(&TrajScene::update));
    connect(m_timeBox, &DoubleValueSlideBox::valueChanged, m_scene, &TrajScene::setCurrentTime);
    connect(m_scenePanel, &ScenePanel::backgroundColorChanged, m_scene, &TrajScene::setBackgroundColor);
    connect(m_lightPanel, &LightPanel::lightColorChanged, m_scene, &TrajScene::setLightColor);
    connect(m_lightPanel, &LightPanel::lightAmbientStrengthChanged, m_scene, &TrajScene::setLightAmbientStrength);
    connect(m_lightPanel, &LightPanel::lightSourcePositionChanged, m_scene, &TrajScene::setLightSourcePosition);
}

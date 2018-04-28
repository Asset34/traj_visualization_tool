#include "addtrajwindow.hpp"

AddTrajWindow::AddTrajWindow(QWidget *parent)
    :QDialog(parent)
{
    /* Configurate path box */
    m_pathBox = new OpenFileBox("Data",
                                "D:/Study/6th_Semester/Geometric_Modeling/CW/AttractorVisualizer/data",
                                "Text data( *.txt )");

    /* Configurate settings panel */
    m_settingsPanel = new TrajSettingsPanel;

    /* Configurate ok button */
    m_okButton = new QPushButton("Ok");
    m_okButton->setFixedHeight(25);
    m_okButton->setFixedWidth(60);

    /* Configurate calcel button */
    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setFixedHeight(25);
    m_cancelButton->setFixedWidth(60);

    /* Configurate buttons layout */
    m_buttonsLayout = new QHBoxLayout;
    m_buttonsLayout->setMargin(0);
    m_buttonsLayout->addWidget(m_okButton);
    m_buttonsLayout->addWidget(m_cancelButton);

    /* Configurate main layout */
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->addWidget(m_pathBox);
    m_mainLayout->addWidget(m_settingsPanel);
    m_mainLayout->addLayout(m_buttonsLayout);

    /* Configurate dialog */
    setLayout(m_mainLayout);
    setMinimumHeight(170);
    setMinimumWidth(200);
    setContentsMargins(5, 5, 5, 5);

    /* Set connections */
    connect(m_okButton, &QPushButton::clicked, this, &AddTrajWindow::accept);
    connect(m_cancelButton, &QPushButton::clicked, this, &AddTrajWindow::reject);
}

Traj *AddTrajWindow::getTraj() const
{
    /* Load traj */
    Traj *traj = TrajUtills::readTraj(m_pathBox->getPath());

    /* Set paremeters */
    traj->setColor(m_settingsPanel->getColor());

    return traj;
}

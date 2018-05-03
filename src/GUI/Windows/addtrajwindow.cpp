#include "addtrajwindow.hpp"

AddTrajWindow::AddTrajWindow(QWidget *parent)
    : QDialog(parent)
{
    /* Configurate name box */
    m_nameBox = new TextInputBox("Name");

    /* Configurate path box */
    m_pathBox = new OpenFileBox("Trajectory",
                                "D:/Study/6th_Semester/Geometric_Modeling/CW/AttractorVisualizer/data",
                                "Text data( *.txt )");

    /* Configurate path section box */
    m_pathSectionBox = new OpenFileBox("Section",
                                       "D:/Study/6th_Semester/Geometric_Modeling/CW/AttractorVisualizer/data",
                                       "Text data( *.txt )");

    /* Configurate ok button */
    m_okButton = new QPushButton("Ok");
    m_okButton->setFixedHeight(25);
    m_okButton->setFixedWidth(60);

    /* Configurate calcel button */
    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setFixedHeight(25);
    m_cancelButton->setFixedWidth(60);

    /* Configurate input layout */
    m_inputLayout = new QVBoxLayout;
    m_inputLayout->setMargin(0);
    m_inputLayout->addWidget(m_nameBox);
    m_inputLayout->addWidget(m_pathBox);
    m_inputLayout->addWidget(m_pathSectionBox);
    m_inputLayout->addStretch(1);

    /* Configurate buttons layout */
    m_buttonsLayout = new QVBoxLayout;
    m_buttonsLayout->setMargin(0);
    m_buttonsLayout->addWidget(m_okButton);
    m_buttonsLayout->addWidget(m_cancelButton);
    m_buttonsLayout->addStretch(1);

    /* Configurate main layout */
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->addLayout(m_inputLayout);
    m_mainLayout->addLayout(m_buttonsLayout);

    /* Configurate dialog */
    setLayout(m_mainLayout);
    setFixedHeight(140);
    setFixedWidth(300);
    setContentsMargins(5, 5, 5, 5);

    /* Set connections */
    connect(m_okButton, &QPushButton::clicked, this, &AddTrajWindow::accept);
    connect(m_cancelButton, &QPushButton::clicked, this, &AddTrajWindow::reject);
}

Traj *AddTrajWindow::getTraj() const
{
    /* Load section */
    QFile file1(m_pathSectionBox->getPath());
    file1.open(QFile::ReadOnly);
    QTextStream stream1(&file1);
    Section section(stream1);

    /* Load trajectory */
    QFile file2(m_pathBox->getPath());
    file2.open(QFile::ReadOnly);
    QTextStream stream2(&file2);
    Traj *traj = new Traj(stream2, section);

    /* Set default trajectory parameters */
    traj->setDisplayed(true);
    traj->setColor(Qt::white);

    return traj;
}

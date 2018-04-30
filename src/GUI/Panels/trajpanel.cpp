#include "trajpanel.hpp"

TrajPanel::TrajPanel(QWidget *parent)
    : QGroupBox(parent)
{
    /* Configurate name box */
    m_nameBox = new OutputBox("Name");

    /* Configurate color box */
    m_colorBox = new ColorSelectBox("Color");

    /* Configurate layout */
    m_layout = new QVBoxLayout;
    m_layout->setMargin(0);
    m_layout->addWidget(m_nameBox);
    m_layout->addWidget(m_colorBox);

    /* Configurate widget */
    setTitle("Trajectory settings");
    setContentsMargins(5, 15, 5, 5);
    setLayout(m_layout);

    /* Set connections */
    connect(m_colorBox, &ColorSelectBox::colorChanged, this, &TrajPanel::setColor);
}

void TrajPanel::setTraj(Traj *traj)
{
    m_traj = traj;

    /* Set current parameters */
    m_nameBox->setText(m_traj->getName());
    m_colorBox->setColor(m_traj->getColor());
}

void TrajPanel::enable()
{
    setEnabled(true);
}

void TrajPanel::disable()
{
    setEnabled(false);
}

void TrajPanel::setColor(const QColor &color)
{
    m_traj->setColor(color);
    emit trajUpdated();
}

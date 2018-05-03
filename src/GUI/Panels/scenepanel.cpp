#include "scenepanel.hpp"

ScenePanel::ScenePanel(QWidget *parent)
    : QGroupBox(parent)
{
    /* Configurate color box */
    m_colorBox = new ColorSelectBox("Background color");
    m_colorBox->setColor(Qt::white);

    /* Configurate layout */
    m_layout = new QVBoxLayout;
    m_layout->setMargin(0);
    m_layout->addWidget(m_colorBox);

    /* Configurate widget */
    setTitle("Scene settings");
    setContentsMargins(5, 15, 5, 5);
    setFixedWidth(150);
    setFixedHeight(70);
    setLayout(m_layout);

    /* Set connections */
    connect(m_colorBox, &ColorSelectBox::colorChanged, this, &ScenePanel::backgroundColorChanged);
}

void ScenePanel::setBackgroundColor(const QColor &color)
{
    m_colorBox->setColor(color);
    emit backgroundColorChanged(color);
}

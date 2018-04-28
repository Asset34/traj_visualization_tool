#include "trajsettingspanel.hpp"

TrajSettingsPanel::TrajSettingsPanel(QWidget *parent)
    : QGroupBox(parent)
{
    /* Configurate color box */
    m_colorBox = new ColorSelectBox("Color");

    /* Configurate layout */
    m_layout = new QVBoxLayout;
    m_layout->setMargin(0);
    m_layout->addWidget(m_colorBox);
    m_layout->addStretch(1);

    /* Configurate widget */
    setTitle("Settings");
    setContentsMargins(5, 15, 5, 5);
    setLayout(m_layout);
}

QColor TrajSettingsPanel::getColor() const
{
    return m_colorBox->getColor();
}

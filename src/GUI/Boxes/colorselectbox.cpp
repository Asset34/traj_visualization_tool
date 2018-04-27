#include "colorselectbox.hpp"

ColorSelectBox::ColorSelectBox(const QString &name,
                               QWidget *parent)
    : QGroupBox(parent),
      m_color(Qt::white)
{
    /* Configurate label */
    m_colorLabel = new QLabel;
    m_colorLabel->setFixedHeight(25);
    m_colorLabel->setAutoFillBackground(true);
    setLabelColor();

    /* Configurate button */
    m_colorButton = new QPushButton("Select");
    m_colorButton->setFixedHeight(25);
    m_colorButton->setFixedWidth(50);

    /* Configurate layout */
    m_layout = new QHBoxLayout;
    m_layout->setMargin(0);
    m_layout->addWidget(m_colorLabel);
    m_layout->addWidget(m_colorButton);

    /* Configurate widget */
    setTitle(name);
    setFixedHeight(50);
    setContentsMargins(5, 5, 5, 0);
    setLayout(m_layout);

    /* Set connections */
    connect(m_colorButton, &QPushButton::clicked, this, &ColorSelectBox::setColor);
}

const QColor &ColorSelectBox::getColor() const
{
    return m_color;
}

void ColorSelectBox::setLabelColor()
{
    QPalette palette = m_colorLabel->palette();
    palette.setColor(m_colorLabel->backgroundRole(), m_color);
    palette.setColor(m_colorLabel->foregroundRole(), m_color);

    m_colorLabel->setPalette(palette);
}

void ColorSelectBox::setColor()
{
    QColor color = QColorDialog::getColor();

    if (color.isValid()) {
        m_color = color;
        setLabelColor();

        emit colorChanged(m_color);
    }
}

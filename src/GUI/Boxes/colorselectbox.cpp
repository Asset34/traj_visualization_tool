#include "colorselectbox.hpp"

ColorSelectBox::ColorSelectBox(const QString &name,
                               const QColor &color,
                               QWidget *parent)
    : AbstractBox(name, parent),
      m_color(color)
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
    setFixedHeight(50);
    setContentsMargins(5, 5, 5, 0);
    setLayout(m_layout);

    /* Set connections */
    connect(m_colorButton, &QPushButton::clicked, this, &ColorSelectBox::setColorFromDialog);
}

const QColor &ColorSelectBox::getColor() const
{
    return m_color;
}

void ColorSelectBox::setColor(const QColor &color)
{
    if (color.isValid()) {
        m_color = color;
        setLabelColor();

        emit colorChanged(m_color);
    }
}

void ColorSelectBox::setLabelColor()
{
    QPalette palette = m_colorLabel->palette();
    palette.setColor(m_colorLabel->backgroundRole(), m_color);
    palette.setColor(m_colorLabel->foregroundRole(), m_color);

    m_colorLabel->setPalette(palette);
}

void ColorSelectBox::setColorFromDialog()
{
    QColor color = QColorDialog::getColor();
    setColor(color);
}

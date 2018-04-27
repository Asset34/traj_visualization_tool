#include "valueslidebox.hpp"

ValueSlideBox::ValueSlideBox(const QString &name, QWidget *parent)
    : QGroupBox(parent)
{
    /* Configurate spin box */
    m_valueSpinBox = new QSpinBox;
    m_valueSpinBox->setFixedWidth(60);

    /* Configurate slider */
    m_valueSlider = new QSlider(Qt::Horizontal);

    /* Configurate layout */
    m_layout = new QHBoxLayout;
    m_layout->setMargin(5);
    m_layout->addWidget(m_valueSpinBox);
    m_layout->addWidget(m_valueSlider);

    /* Configurate widget */
    setTitle(name);

    setLayout(m_layout);
    setFixedHeight(40);

    /* Set connections */
    connect(m_valueSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &ValueSlideBox::valueChanged);
    connect(m_valueSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            m_valueSlider, &QSlider::setValue);
    connect(m_valueSlider, &QSlider::valueChanged, m_valueSpinBox, &QSpinBox::setValue);
}

QString ValueSlideBox::getName() const
{
    return title();
}

void ValueSlideBox::setName(const QString &name)
{
    setTitle(name);
}

int ValueSlideBox::getValue() const
{
    return m_valueSpinBox->value();
}

int ValueSlideBox::getMaximum() const
{
    return m_valueSpinBox->maximum();
}

void ValueSlideBox::setMaximum(int max) const
{
    m_valueSpinBox->setMaximum(max);
    m_valueSlider->setMaximum(max);
}

int ValueSlideBox::getMinimum() const
{
    return m_valueSpinBox->minimum();
}

void ValueSlideBox::setMinimum(int min)
{
    m_valueSpinBox->setMinimum(min);
    m_valueSlider->setMinimum(min);
}

int ValueSlideBox::getStep() const
{
    return m_valueSpinBox->singleStep();
}

void ValueSlideBox::setStep(int step)
{
    m_valueSpinBox->setSingleStep(step);
    m_valueSlider->setSingleStep(step);
}

void ValueSlideBox::setValue(int value)
{
    m_valueSpinBox->setValue(value);
    m_valueSlider->setValue(value);
}

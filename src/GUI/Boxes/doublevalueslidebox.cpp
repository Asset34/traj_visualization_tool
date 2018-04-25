#include "doublevalueslidebox.hpp"

DoubleValueSlideBox::DoubleValueSlideBox(const QString &name, int decimals, QWidget *parent)
    : QGroupBox(parent)
{
    /* Configurate spin box */
    m_valueSpinBox = new QDoubleSpinBox;
    m_valueSpinBox->setFixedWidth(60);

    /* Configurate slider */
    m_valueSlider = new QSlider(Qt::Horizontal);

    /* Configurate layout */
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setMargin(5);
    m_mainLayout->addWidget(m_valueSpinBox);
    m_mainLayout->addWidget(m_valueSlider);

    /* Configurate widget */
    setTitle(name);
    setLayout(m_mainLayout);
    setFixedHeight(40);
    setDecimals(decimals);

    /* Configurate connections */
    connect(m_valueSpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &DoubleValueSlideBox::valueChanged);
    connect(m_valueSpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &DoubleValueSlideBox::setSliderValue);
    connect(m_valueSlider, &QSlider::valueChanged, this, &DoubleValueSlideBox::setSpinBoxValue);
}

QString DoubleValueSlideBox::getName() const
{
    return title();
}

void DoubleValueSlideBox::setName(const QString &name)
{
    setTitle(name);
}

double DoubleValueSlideBox::getValue() const
{
    return m_valueSpinBox->value();
}

double DoubleValueSlideBox::getMaximum() const
{
    return m_valueSpinBox->maximum();
}

void DoubleValueSlideBox::setMaximum(double max) const
{
    m_valueSpinBox->setMaximum(max);
    m_valueSlider->setMaximum(convertValue(max));
}

double DoubleValueSlideBox::getMinimum() const
{
    return m_valueSpinBox->minimum();
}

void DoubleValueSlideBox::setMinimum(double min)
{
    m_valueSpinBox->setMinimum(min);
    m_valueSlider->setMinimum(convertValue(min));
}

int DoubleValueSlideBox::getDecimals() const
{
    return m_valueSpinBox->decimals();
}

void DoubleValueSlideBox::setDecimals(int d)
{
    m_convertFactor = qPow(10, d);
    m_valueSpinBox->setDecimals(d);
}

double DoubleValueSlideBox::getStep() const
{
    return m_valueSpinBox->singleStep();
}

void DoubleValueSlideBox::setStep(double step)
{
    m_valueSpinBox->setSingleStep(step);
    m_valueSlider->setSingleStep(convertValue(step));
}

void DoubleValueSlideBox::setValue(double value)
{
    m_valueSpinBox->setValue(value);
    setSliderValue(value);
}

int DoubleValueSlideBox::convertValue(double value) const
{
    return value * m_convertFactor;
}

double DoubleValueSlideBox::convertValue(int value) const
{
    return double(value) / m_convertFactor;
}

void DoubleValueSlideBox::setSpinBoxValue(int value)
{
    m_valueSpinBox->setValue(convertValue(value));
}

void DoubleValueSlideBox::setSliderValue(double value)
{
    m_valueSlider->setValue(convertValue(value));
}

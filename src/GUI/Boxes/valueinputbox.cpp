#include "valueinputbox.hpp"

ValueInputBox::ValueInputBox(const QString &name, QWidget *parent)
    : SimpleAbstractBox(name, parent)
{
    /* Configurate spin box */
    m_valueSpinBox = new QSpinBox;
    m_valueSpinBox->setFixedWidth(60);

    /* Configurate layout */
    m_layout = new QHBoxLayout;
    m_layout->setMargin(0);
    m_layout->addWidget(m_nameLabel);
    m_layout->addWidget(m_valueSpinBox);

    /* Configurate widget */
    setLayout(m_layout);
    setFixedHeight(20);

    /* Set connections */
    connect(m_valueSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &ValueInputBox::valueChanged);
}

int ValueInputBox::getValue() const
{
    return m_valueSpinBox->value();
}

int ValueInputBox::getMaximum() const
{
    return m_valueSpinBox->maximum();
}

void ValueInputBox::setMaximum(int max) const
{
    m_valueSpinBox->setMaximum(max);
}

int ValueInputBox::getMinimum() const
{
    return m_valueSpinBox->minimum();
}

void ValueInputBox::setMinimum(int min)
{
    m_valueSpinBox->setMinimum(min);
}

int ValueInputBox::getStep() const
{
    return m_valueSpinBox->singleStep();
}

void ValueInputBox::setStep(int step)
{
    m_valueSpinBox->setSingleStep(step);
}

void ValueInputBox::setValue(int value)
{
    m_valueSpinBox->setValue(value);
}

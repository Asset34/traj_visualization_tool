#include "valueinputbox.hpp"

ValueInputBox::ValueInputBox(const QString &name, QWidget *parent)
    : QWidget(parent)
{
    /* Configurate label */
    m_nameLabel = new QLabel(name);
    m_nameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    /* Configurate spin box */
    m_valueSpinBox = new QSpinBox;
    m_valueSpinBox->setFixedWidth(60);

    /* Configurate layout */
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->addWidget(m_nameLabel);
    m_mainLayout->addWidget(m_valueSpinBox);

    /* Configurate widget */
    setLayout(m_mainLayout);
    setFixedHeight(20);

    /* Configurate connections */
    connect(m_valueSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &ValueInputBox::valueChanged);
}

QString ValueInputBox::getName() const
{
    return m_nameLabel->text();
}

void ValueInputBox::setName(const QString &name)
{
    m_nameLabel->setText(name);
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

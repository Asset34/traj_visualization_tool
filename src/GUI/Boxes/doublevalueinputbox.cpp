#include "doublevalueinputbox.hpp"

DoubleValueInputBox::DoubleValueInputBox(const QString &name, QWidget *parent)
    : QWidget(parent)
{
    /* Configurate label */
    m_nameLabel = new QLabel(name);
    m_nameLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    /* Configurate spin box */
    m_valueSpinBox = new QDoubleSpinBox;
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
    connect(m_valueSpinBox, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &DoubleValueInputBox::valueChanged);
}

QString DoubleValueInputBox::getName() const
{
    return m_nameLabel->text();
}

void DoubleValueInputBox::setName(const QString &name)
{
    m_nameLabel->setText(name);
}

double DoubleValueInputBox::getValue() const
{
    return m_valueSpinBox->value();
}

double DoubleValueInputBox::getMaximum() const
{
    return m_valueSpinBox->maximum();
}

void DoubleValueInputBox::setMaximum(double max) const
{
    m_valueSpinBox->setMaximum(max);
}

double DoubleValueInputBox::getMinimum() const
{
    return m_valueSpinBox->minimum();
}

void DoubleValueInputBox::setMinimum(double min)
{
    m_valueSpinBox->setMinimum(min);
}

double DoubleValueInputBox::getStep() const
{
    return m_valueSpinBox->singleStep();
}

void DoubleValueInputBox::setStep(double step)
{
    m_valueSpinBox->setDecimals(Utills::numDecimals(step));
    m_valueSpinBox->setSingleStep(step);
}

void DoubleValueInputBox::setValue(double value)
{
    m_valueSpinBox->setValue(value);
}

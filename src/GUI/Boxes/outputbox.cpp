#include "outputbox.hpp"

OutputBox::OutputBox(const QString &name, QWidget *parent)
    : SimpleAbstractBox(name, parent)
{
    /* Configurate value label */
    m_valueLabel = new QLabel;

    /* Configurate layout */
    m_layout = new QHBoxLayout;
    m_layout->setMargin(0);
    m_layout->addWidget(m_nameLabel);
    m_layout->addWidget(m_valueLabel);

    /* Configurate widget */
    setLayout(m_layout);
    setFixedHeight(25);
}

void OutputBox::setText(const QString &text)
{
    m_valueLabel->setText(text);
}

void OutputBox::setValue(int value)
{
    m_valueLabel->setText(QString::number(value));
}

void OutputBox::setValue(double value)
{
    m_valueLabel->setText(QString::number(value));
}

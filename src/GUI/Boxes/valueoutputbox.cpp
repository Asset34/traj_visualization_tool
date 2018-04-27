#include "valueoutputbox.hpp"

ValueOutputBox::ValueOutputBox(const QString &name, QWidget *parent)
    : QWidget(parent)
{
    /* Configurate name label */
    m_nameLabel = new QLabel(name);
    m_nameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    /* Configurate value label */
    m_valueLabel = new QLabel;
    m_valueLabel->setFixedWidth(40);

    /* Configurate layout */
    m_layout = new QHBoxLayout;
    m_layout->setMargin(0);
    m_layout->addWidget(m_nameLabel);
    m_layout->addWidget(m_valueLabel);

    /* Configurate widget */
    setLayout(m_layout);
    setFixedHeight(35);
}

QString ValueOutputBox::getName() const
{
    return m_nameLabel->text();
}

void ValueOutputBox::setName(const QString &name)
{
    m_nameLabel->setText(name);
}

void ValueOutputBox::setValue(int value)
{
    m_valueLabel->setText(QString::number(value));
}

void ValueOutputBox::setValue(double value)
{
    m_valueLabel->setText(QString::number(value));
}

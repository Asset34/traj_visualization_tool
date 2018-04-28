#include "flagsetbox.hpp"

FlagSetBox::FlagSetBox(const QString &name, bool state, QWidget *parent)
    : QWidget(parent)
{
    /* Configurate label */
    m_nameLabel = new QLabel(name);
    m_nameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    /* Configurate check box */
    m_flagCheckBox = new QCheckBox;
    m_flagCheckBox->setFixedWidth(20);
    m_flagCheckBox->setChecked(state);

    /* Configurate layout */
    m_layout = new QHBoxLayout;
    m_layout->setMargin(0);
    m_layout->addWidget(m_flagCheckBox);
    m_layout->addWidget(m_nameLabel);

    /* Configurate widget */
    setLayout(m_layout);
    setFixedHeight(20);

    /* Set connections */
    connect(m_flagCheckBox, &QCheckBox::stateChanged, this, &FlagSetBox::stateChanged);
}

QString FlagSetBox::getName() const
{
    return m_nameLabel->text();
}

void FlagSetBox::setName(const QString &name)
{
    m_nameLabel->setText(name);
}

bool FlagSetBox::getState() const
{
    return m_flagCheckBox->isChecked();
}

void FlagSetBox::setState(bool state)
{
    m_flagCheckBox->setChecked(state);
    emit stateChanged(state);
}

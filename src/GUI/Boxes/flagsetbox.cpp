#include "flagsetbox.hpp"

FlagSetBox::FlagSetBox(const QString &name, QWidget *parent)
    : QWidget(parent)
{
    /* Configurate label */
    m_nameLabel = new QLabel(name);
    m_nameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    /* Configurate check box */
    m_flagCheckBox = new QCheckBox;
    m_flagCheckBox->setFixedWidth(20);
    m_flagCheckBox->setCheckState(Qt::Unchecked);

    /* Configurate layout */
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->addWidget(m_flagCheckBox);
    m_mainLayout->addWidget(m_nameLabel);

    /* Configurate widget */
    setLayout(m_mainLayout);
    setFixedHeight(20);

    /* Configurate connections */
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

Qt::CheckState FlagSetBox::getState() const
{
    return m_flagCheckBox->checkState();
}

void FlagSetBox::setState(Qt::CheckState state)
{
    m_flagCheckBox->setCheckState(state);
}

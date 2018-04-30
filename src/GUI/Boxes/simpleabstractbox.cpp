#include "simpleabstractbox.hpp"

SimpleAbstractBox::SimpleAbstractBox(const QString &name, QWidget *parent)
    : QWidget(parent)
{
    m_nameLabel = new QLabel(name);
    m_nameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

QString SimpleAbstractBox::getName() const
{
    return m_nameLabel->text();
}

void SimpleAbstractBox::setName(const QString &name)
{
    m_nameLabel->setText(name);
}

void SimpleAbstractBox::enable()
{
    setEnabled(true);
}

void SimpleAbstractBox::disable()
{
    setEnabled(false);
}

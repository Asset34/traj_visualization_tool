#include "abstractbox.hpp"

AbstractBox::AbstractBox(const QString &name, QWidget *parent)
    : QGroupBox(parent)
{
    setTitle(name);
}

QString AbstractBox::getName() const
{
    return title();
}

void AbstractBox::setName(const QString &name)
{
    setTitle(name);
}

void AbstractBox::enable()
{
    setEnabled(true);
}

void AbstractBox::disable()
{
    setEnabled(false);
}

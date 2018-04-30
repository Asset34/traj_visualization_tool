#ifndef VALUEOUTPUTBOX_HPP
#define VALUEOUTPUTBOX_HPP

#include <QHBoxLayout>

#include <QLabel>

#include "simpleabstractbox.hpp"

class OutputBox : public SimpleAbstractBox
{
    Q_OBJECT

public:
    explicit OutputBox(const QString &name = QString(),
                       QWidget *parent = nullptr);

public slots:
    void setText(const QString &text);
    void setValue(int value);
    void setValue(double value);

private:
    QHBoxLayout *m_layout;
    QLabel *m_valueLabel;

};

#endif // VALUEOUTPUTBOX_HPP

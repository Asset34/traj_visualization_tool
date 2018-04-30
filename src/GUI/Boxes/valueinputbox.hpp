#ifndef VALUEINPUTBOX_HPP
#define VALUEINPUTBOX_HPP

#include <QHBoxLayout>

#include <QSpinBox>

#include "simpleabstractbox.hpp"

class ValueInputBox : public SimpleAbstractBox
{
    Q_OBJECT

public:
    explicit ValueInputBox(const QString &name = QString(),
                           QWidget *parent = nullptr);

    int getValue() const;

    int getMaximum() const;
    void setMaximum(int max) const;

    int getMinimum() const;
    void setMinimum(int min);

    int getStep() const;
    void setStep(int step);

public slots:
    void setValue(int value);

private:
    QHBoxLayout *m_layout;
    QSpinBox *m_valueSpinBox;

signals:
    void valueChanged(int value);

};

#endif // VALUEINPUTBOX_HPP

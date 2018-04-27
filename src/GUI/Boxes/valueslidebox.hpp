#ifndef VALUESLIDEBOX_HPP
#define VALUESLIDEBOX_HPP

#include <QHBoxLayout>

#include <QGroupBox>
#include <QSpinBox>
#include <QSlider>

class ValueSlideBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit ValueSlideBox(const QString &name = QString(),
                           QWidget *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);

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
    QSlider *m_valueSlider;

signals:
    void valueChanged(int value);

};

#endif // VALUESLIDEBOX_HPP

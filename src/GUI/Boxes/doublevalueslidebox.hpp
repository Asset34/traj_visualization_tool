#ifndef DOUBLEVALUESLIDEBOX_HPP
#define DOUBLEVALUESLIDEBOX_HPP

#include <QHBoxLayout>

#include <QGroupBox>
#include <QSlider>
#include <QDoubleSpinBox>

#include <cmath>

#include "../../utills.hpp"

class DoubleValueSlideBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit DoubleValueSlideBox(const QString &name = "", QWidget *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);
    double getValue() const;
    double getMaximum() const;
    void setMaximum(double max) const;
    double getMinimum() const;
    void setMinimum(double min);
    double getStep() const;
    void setStep(double step);

public slots:
    void setValue(double value);

private:
    QHBoxLayout *m_mainLayout;
    QDoubleSpinBox *m_valueSpinBox;
    QSlider *m_valueSlider;

    int convertValue(double value) const;
    double convertValue(int value) const;

private slots:
    void setSpinBoxValue(int value);
    void setSliderValue(double value);

signals:
    void valueChanged(double value);

};

#endif // DOUBLEVALUESLIDEBOX_HPP

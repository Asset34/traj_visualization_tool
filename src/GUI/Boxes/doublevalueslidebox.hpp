#ifndef DOUBLEVALUESLIDEBOX_HPP
#define DOUBLEVALUESLIDEBOX_HPP

#include <QHBoxLayout>

#include <QGroupBox>
#include <QSlider>
#include <QDoubleSpinBox>

#include <QtMath>

class DoubleValueSlideBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit DoubleValueSlideBox(const QString &name = QString(),
                                 int decimals = 2,
                                 double step = 0.1,
                                 QWidget *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);

    double getValue() const;
    double getMaximum() const;
    double getMinimum() const;
    int getDecimals() const;
    double getStep() const;

public slots:
    void setValue(double value);
    void setMaximum(double max);
    void setMinimum(double min);
    void setDecimals(int d);
    void setStep(double step);

private:
    QHBoxLayout *m_mainLayout;
    QDoubleSpinBox *m_valueSpinBox;
    QSlider *m_valueSlider;

    int m_convertFactor;

    int convertValue(double value) const;
    double convertValue(int value) const;

private slots:
    void setSpinBoxValue(int value);
    void setSliderValue(double value);

signals:
    void valueChanged(double value);

};

#endif // DOUBLEVALUESLIDEBOX_HPP

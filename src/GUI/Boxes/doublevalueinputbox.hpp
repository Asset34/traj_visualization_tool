#ifndef DOUBLEVALUEINPUTBOX_HPP
#define DOUBLEVALUEINPUTBOX_HPP

#include <QHBoxLayout>

#include <QLabel>
#include <QDoubleSpinBox>

class DoubleValueInputBox : public QWidget
{
    Q_OBJECT

public:
    explicit DoubleValueInputBox(const QString &name = QString(),
                                 int decimals = 2,
                                 double step = 0.1,
                                 QWidget *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);

    double getValue() const;

    double getMaximum() const;
    void setMaximum(double max) const;

    double getMinimum() const;
    void setMinimum(double min);

    int getDecimals() const;
    void setDecimals(int d);

    double getStep() const;
    void setStep(double step);

public slots:
    void setValue(double value);

private:
    QHBoxLayout *m_layout;
    QLabel *m_nameLabel;
    QDoubleSpinBox *m_valueSpinBox;

signals:
    void valueChanged(double value);

};

#endif // DOUBLEVALUEINPUTBOX_HPP

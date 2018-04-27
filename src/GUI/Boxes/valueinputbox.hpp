#ifndef VALUEINPUTBOX_HPP
#define VALUEINPUTBOX_HPP

#include <QHBoxLayout>

#include <QLabel>
#include <QSpinBox>

class ValueInputBox : public QWidget
{
    Q_OBJECT

public:
    explicit ValueInputBox(const QString &name = QString(),
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
    QLabel *m_nameLabel;
    QSpinBox *m_valueSpinBox;

signals:
    void valueChanged(int value);

};

#endif // VALUEINPUTBOX_HPP

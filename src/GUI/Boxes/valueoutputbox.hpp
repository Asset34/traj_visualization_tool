#ifndef VALUEOUTPUTBOX_HPP
#define VALUEOUTPUTBOX_HPP

#include <QHBoxLayout>

#include <QLabel>

class ValueOutputBox : public QWidget
{
    Q_OBJECT

public:
    explicit ValueOutputBox(const QString &name = QString(),
                            QWidget *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);

public slots:
    void setValue(int value);
    void setValue(double value);

private:
    QHBoxLayout *m_layout;
    QLabel *m_nameLabel;
    QLabel *m_valueLabel;

};

#endif // VALUEOUTPUTBOX_HPP

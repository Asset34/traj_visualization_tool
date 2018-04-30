#ifndef ABSTRACTBOX_HPP
#define ABSTRACTBOX_HPP

#include <QGroupBox>

class AbstractBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit AbstractBox(const QString &name = QString(),
                         QWidget *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);

public slots:
    void enable();
    void disable();

};

#endif // ABSTRACTBOX_HPP

#ifndef SIMPLEABSTRACTBOX_HPP
#define SIMPLEABSTRACTBOX_HPP

#include <QWidget>

#include <QLabel>

class SimpleAbstractBox : public QWidget
{
    Q_OBJECT

public:
    explicit SimpleAbstractBox(const QString &name = QString(),
                               QWidget *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);

protected:
    QLabel *m_nameLabel;

public slots:
    void enable();
    void disable();
};

#endif // SIMPLEABSTRACTBOX_HPP

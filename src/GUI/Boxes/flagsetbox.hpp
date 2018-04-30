#ifndef FLAGSETBOX_HPP
#define FLAGSETBOX_HPP

#include <QHBoxLayout>

#include <QCheckBox>

#include "simpleabstractbox.hpp"

class FlagSetBox : public SimpleAbstractBox
{
    Q_OBJECT

public:
    explicit FlagSetBox(const QString &name = QString(),
                        bool state = false,
                        QWidget *parent = nullptr);

    bool getState() const;

public slots:
    void setState(bool state);

private:
    QHBoxLayout *m_layout;
    QCheckBox *m_flagCheckBox;

signals:
    void stateChanged(bool state);

};

#endif // FLAGSETBOX_HPP

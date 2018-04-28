#ifndef FLAGSETBOX_HPP
#define FLAGSETBOX_HPP

#include <QHBoxLayout>

#include <QLabel>
#include <QCheckBox>

class FlagSetBox : public QWidget
{
    Q_OBJECT

public:
    explicit FlagSetBox(const QString &name = QString(),
                        bool state = false,
                        QWidget *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);

    bool getState() const;

public slots:
    void setState(bool state);

private:
    QHBoxLayout *m_layout;
    QLabel *m_nameLabel;
    QCheckBox *m_flagCheckBox;

signals:
    void stateChanged(bool state);

};

#endif // FLAGSETBOX_HPP

#ifndef FLAGSETBOX_HPP
#define FLAGSETBOX_HPP

#include <QWidget>

#include <QHBoxLayout>

#include <QLabel>
#include <QCheckBox>

class FlagSetBox : public QWidget
{
    Q_OBJECT

public:
    explicit FlagSetBox(const QString &name = "",QWidget *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);
    Qt::CheckState getState() const;

public slots:
    void setState(Qt::CheckState state);

private:
    QHBoxLayout *m_mainLayout;
    QLabel *m_nameLabel;
    QCheckBox *m_flagCheckBox;

signals:
    void stateChanged(int state);

};

#endif // FLAGSETBOX_HPP

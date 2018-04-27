#ifndef COLORSELECTBOX_HPP
#define COLORSELECTBOX_HPP

#include <QHBoxLayout>

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

#include <QColor>
#include <QPalette>
#include <QColorDialog>

class ColorSelectBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit ColorSelectBox(const QString &name = QString(),
                            QWidget *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);

    const QColor &getColor() const;

private:
    QHBoxLayout *m_layout;
    QLabel *m_colorLabel;
    QPushButton *m_colorButton;

    QColor m_color;

    void setLabelColor();

private slots:
    void setColor();

signals:
    void colorChanged(const QColor &color);

};

#endif // COLORSELECTBOX_HPP

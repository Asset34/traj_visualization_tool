#ifndef COLORSELECTBOX_HPP
#define COLORSELECTBOX_HPP

#include <QHBoxLayout>

#include <QLabel>
#include <QPushButton>

#include <QColor>
#include <QPalette>
#include <QColorDialog>

#include "abstractbox.hpp"

class ColorSelectBox : public AbstractBox
{
    Q_OBJECT

public:
    explicit ColorSelectBox(const QString &name = QString(),
                            const QColor &color = Qt::white,
                            QWidget *parent = nullptr);

    const QColor &getColor() const;
    void setColor(const QColor &color);

private:
    QHBoxLayout *m_layout;
    QLabel *m_colorLabel;
    QPushButton *m_colorButton;

    QColor m_color;

    void setLabelColor();

private slots:
    void setColorFromDialog();

signals:
    void colorChanged(const QColor &color);

};

#endif // COLORSELECTBOX_HPP

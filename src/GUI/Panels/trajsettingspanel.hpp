#ifndef TRAJSETTINGSPANEL_HPP
#define TRAJSETTINGSPANEL_HPP

#include <QVBoxLayout>

#include <QGroupBox>

#include "../../Opengl/traj.hpp"
#include "../Boxes/colorselectbox.hpp"

class TrajSettingsPanel : public QGroupBox
{
    Q_OBJECT

public:
    explicit TrajSettingsPanel(QWidget *parent = nullptr);

    QColor getColor() const;

public slots:

private:
    QVBoxLayout *m_layout;
    ColorSelectBox *m_colorBox;

signals:
    void colorChanged(const QColor &color);
};

#endif // TRAJSETTINGSPANEL_HPP

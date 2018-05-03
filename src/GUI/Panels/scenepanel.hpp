#ifndef SCENEPANEL_HPP
#define SCENEPANEL_HPP

#include <QVBoxLayout>

#include <QGroupBox>

#include "../Boxes/colorselectbox.hpp"

class ScenePanel : public QGroupBox
{
    Q_OBJECT

public:
    explicit ScenePanel(QWidget *parent = nullptr);

public slots:
    void setBackgroundColor(const QColor &color);

private:
    QVBoxLayout *m_layout;
    ColorSelectBox *m_colorBox;

signals:
    void backgroundColorChanged(const QColor &color);

};

#endif // SCENEPANEL_HPP

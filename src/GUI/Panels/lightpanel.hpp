#ifndef LIGHTPANEL_HPP
#define LIGHTPANEL_HPP

#include <QVBoxLayout>

#include <QGroupBox>

#include "../Boxes/colorselectbox.hpp"
#include "../Boxes/vectorinputbox.hpp"
#include "../Boxes/doublevalueslidebox.hpp"

class LightPanel : public QGroupBox
{
    Q_OBJECT

public:
    explicit LightPanel(QWidget *parent = nullptr);

public slots:
    void setLightColor(const QColor &color);
    void setlightAmbientStrength(float strength);
    void setLightSourcePosition(const QVector3D &vec);

private:
    QVBoxLayout *m_layout;
    ColorSelectBox *m_lightColorBox;
    DoubleValueSlideBox *m_lightAmbientStrengthBox;
    VectorInputBox *m_lightSourcePosBox;

signals:
    void lightColorChanged(const QColor &color);
    void lightAmbientStrengthChanged(double strength);
    void lightSourcePositionChanged(const QVector3D &vec);

};

#endif // LIGHTPANEL_HPP

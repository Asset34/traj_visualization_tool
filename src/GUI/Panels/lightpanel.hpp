#ifndef LIGHTPANEL_HPP
#define LIGHTPANEL_HPP

#include <QVBoxLayout>

#include <QGroupBox>

#include "../boxes/colorselectbox.hpp"
#include "../boxes/vectorinputbox.hpp"
#include "../boxes/doublevalueslidebox.hpp"

class LightPanel : public QGroupBox
{
    Q_OBJECT

public:
    explicit LightPanel(QWidget *parent = nullptr);

public slots:
    void setlightAmbientStrength(float strength);
    void setLightColor(const QColor &color);
    void setLightSourcePosition(const QVector3D &vec);

private:
    QVBoxLayout *m_layout;
    DoubleValueSlideBox *m_lightAmbientStrengthBox;
    ColorSelectBox *m_lightColorBox;
    VectorInputBox *m_lightSourcePosBox;

signals:
    void lightAmbientStrengthChanged(double strength);
    void lightColorChanged(const QColor &color);    
    void lightSourcePositionChanged(const QVector3D &vec);

};

#endif // LIGHTPANEL_HPP

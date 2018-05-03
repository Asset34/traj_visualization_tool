#include "lightpanel.hpp"

LightPanel::LightPanel(QWidget *parent)
    : QGroupBox(parent)
{
    /* Configurate light color box */
    m_lightColorBox = new ColorSelectBox("Light sourde color");
    m_lightColorBox->setColor(Qt::white);

    /* Configurate ambient box */
    m_lightAmbientStrengthBox = new DoubleValueSlideBox("Ambient light");
    m_lightAmbientStrengthBox->setMinimum(0.0);
    m_lightAmbientStrengthBox->setMaximum(1.0);
    m_lightAmbientStrengthBox->setStep(0.01);
    m_lightAmbientStrengthBox->setValue(0.1);

    /* Configurate light position box */
    m_lightSourcePosBox = new VectorInputBox("Light source position");
    m_lightSourcePosBox->setValue({0.0, 0.0, 10.0});

    /* Configurate  layout */
    m_layout = new QVBoxLayout;
    m_layout->setMargin(0);
    m_layout->addWidget(m_lightColorBox);
    m_layout->addWidget(m_lightAmbientStrengthBox);
    m_layout->addWidget(m_lightSourcePosBox);

    /* Configurate panel */
    setTitle("Light settings");
    setFixedWidth(200);
    setContentsMargins(5, 15, 5, 5);
    setLayout(m_layout);

    /* Set connections */
    connect(m_lightColorBox, &ColorSelectBox::colorChanged, this, &LightPanel::lightColorChanged);
    connect(m_lightAmbientStrengthBox, &DoubleValueSlideBox::valueChanged, this, &LightPanel::lightAmbientStrengthChanged);
    connect(m_lightSourcePosBox, &VectorInputBox::valueChanged, this, &LightPanel::lightSourcePositionChanged);
}

void LightPanel::setLightColor(const QColor &color)
{
    m_lightColorBox->setColor(color);
    emit lightColorChanged(color);
}

void LightPanel::setlightAmbientStrength(float strength)
{
    m_lightAmbientStrengthBox->setValue(strength);
    emit lightAmbientStrengthChanged(strength);
}

void LightPanel::setLightSourcePosition(const QVector3D &vec)
{
    m_lightSourcePosBox->setValue(vec);
    emit lightSourcePositionChanged(vec);
}

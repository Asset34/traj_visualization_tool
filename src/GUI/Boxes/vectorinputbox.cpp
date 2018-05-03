#include "vectorinputbox.hpp"

VectorInputBox::VectorInputBox(const QString &name, QWidget *parent)
    : AbstractBox(name, parent)
{
    /* Configurate x coordinate box */
    m_xBox = new DoubleValueInputBox("x:");
    m_xBox->setMinimum(-1000000.0);
    m_xBox->setMaximum(1000000.0);
    m_xBox->setStep(0.1);

    /* Configurate y coordinate box */
    m_yBox = new DoubleValueInputBox("y:");
    m_yBox->setMinimum(-1000000.0);
    m_yBox->setMaximum(1000000.0);
    m_yBox->setStep(0.1);

    /* Configurate z coordinate box */
    m_zBox = new DoubleValueInputBox("z:");
    m_zBox->setMinimum(-1000000.0);
    m_zBox->setMaximum(1000000.0);
    m_zBox->setStep(0.1);

    /* Configurate layout */
    m_layout = new QVBoxLayout;
    m_layout->setMargin(0);
    m_layout->addWidget(m_xBox);
    m_layout->addWidget(m_yBox);
    m_layout->addWidget(m_zBox);
    m_layout->addStretch(1);

    /* Configurate widget */
    setFixedHeight(100);
    setContentsMargins(5, 20, 5, 0);
    setLayout(m_layout);

    /* Set connections */
    connect(m_xBox, &DoubleValueInputBox::valueChanged, this, &VectorInputBox::setValues);
    connect(m_yBox, &DoubleValueInputBox::valueChanged, this, &VectorInputBox::setValues);
    connect(m_zBox, &DoubleValueInputBox::valueChanged, this, &VectorInputBox::setValues);
}

void VectorInputBox::setValue(const QVector3D &vec)
{
    m_xBox->setValue(vec.x());
    m_yBox->setValue(vec.y());
    m_zBox->setValue(vec.z());
}

void VectorInputBox::setValues()
{
    m_vec.setX(m_xBox->getValue());
    m_vec.setY(m_yBox->getValue());
    m_vec.setZ(m_zBox->getValue());

    emit valueChanged(m_vec);
}

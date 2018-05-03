#ifndef VECTORINPUTBOX_HPP
#define VECTORINPUTBOX_HPP

#include <QVBoxLayout>
#include <QVector3D>

#include "abstractbox.hpp"
#include "doublevalueinputbox.hpp"

class VectorInputBox : public AbstractBox
{
    Q_OBJECT

public:
    explicit VectorInputBox(const QString &name = QString(),
                            QWidget *parent = nullptr);

public slots:
    void setValue(const QVector3D &vec);

private:
    QVBoxLayout *m_layout;
    DoubleValueInputBox *m_xBox;
    DoubleValueInputBox *m_yBox;
    DoubleValueInputBox *m_zBox;

    QVector3D m_vec;

private slots:
    void setValues();

signals:
    void valueChanged(const QVector3D &vec);
};

#endif // VECTORINPUTBOX_HPP

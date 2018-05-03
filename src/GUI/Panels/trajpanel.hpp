#ifndef TRAJPANEL_HPP
#define TRAJPANEL_HPP

#include <QVBoxLayout>

#include <QGroupBox>

#include "../boxes/outputbox.hpp"
#include "../boxes/colorselectbox.hpp"
#include "../../sceneobj/traj.hpp"

class TrajPanel : public QGroupBox
{
    Q_OBJECT

public:
    explicit TrajPanel(QWidget *parent = nullptr);

public slots:
    void setTraj(Traj *traj);
    void enable();
    void disable();

private:
    QVBoxLayout *m_layout;
    OutputBox *m_nameBox;
    ColorSelectBox *m_colorBox;

    Traj *m_traj;

private slots:
    void setColor(const QColor &color);

signals:
    void trajUpdated();

};

#endif // TRAJPANEL_HPP

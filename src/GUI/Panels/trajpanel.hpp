#ifndef TRAJPANEL_HPP
#define TRAJPANEL_HPP

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QGroupBox>
#include <QListWidget>
#include <QPushButton>

#include <QVector3D>

#include "../../Opengl/traj.hpp"
#include "../Windows/addtrajwindow.hpp"

class TrajPanel : public QGroupBox
{
    Q_OBJECT

public:
    explicit TrajPanel(QWidget *parent = nullptr);

public slots:
    void addTraj();
    void deleteTraj();
    void editTraj();
    void focusTraj();
    void setDisplayStatus(QListWidgetItem *item);

private:
    QHBoxLayout *m_mainLayout;
    QVBoxLayout *m_buttonsLayout;
    QListWidget *m_trajList;
    QPushButton *m_addButton;
    QPushButton *m_deleteButton;
    QPushButton *m_editButton;
    QPushButton *m_focusButton;

    QString convertInitials(const QVector3D &initials);

    QList<Traj*> m_trajs;

    double m_minBeginTime;
    double m_maxEndTime;
    double m_minTimeStep;

    void updateTimeBorders(Traj *traj);

signals:
    void trajAdded(Traj *ptraj);
    void trajDeleted(int pos);
    void trajFocused(Traj *traj);
    void trajEdited();
    void trajDisplayStatusChanged();
    void trajMinBeginTimeChanged(double time);
    void trajMaxEndTimeCHanged(double time);
    void trajMinTimeStepChanged(double step);
};

#endif // TRAJPANEL_HPP

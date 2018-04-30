#ifndef TRAJCONTROLPANEL_HPP
#define TRAJCONTROLPANEL_HPP

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QGroupBox>
#include <QListWidget>
#include <QPushButton>

#include <QVector3D>

#include "../../Opengl/traj.hpp"
#include "../Windows/addtrajwindow.hpp"

class TrajControlPanel : public QGroupBox
{
    Q_OBJECT

public:
    explicit TrajControlPanel(QWidget *parent = nullptr);

private:
    QHBoxLayout *m_mainLayout;
    QVBoxLayout *m_buttonsLayout;
    QListWidget *m_trajList;
    QPushButton *m_addButton;
    QPushButton *m_deleteButton;
    QPushButton *m_selectButton;
    QPushButton *m_focusButton;

    QList<Traj*> m_trajs;

    double m_minBeginTime;
    double m_maxEndTime;
    double m_minTimeStep;

    void updateGeneralTimeValues();

    bool checkIndex(int index) const;
    bool checkFirst() const;
    bool checkLast() const;

private slots:
    void addTraj();
    void deleteTraj();
    void selectTraj();
    void focusTraj();
    void setTrajDisplayStatus(QListWidgetItem *item);

signals:
    void trajAdded(Traj *ptraj);
    void trajDeleted(int pos);
    void trajFocused(Traj *traj);
    void trajSelected(Traj *traj);
    void trajDisplayStatusChanged();

    void minBeginTimeChanged(double time);
    void maxEndTimeChanged(double time);
    void minTimeStepChanged(double step);

    void firstTrajWasAdded(Traj *traj);
    void allTrajWasDeleted();
};

#endif // TRAJCONTROLPANEL_HPP

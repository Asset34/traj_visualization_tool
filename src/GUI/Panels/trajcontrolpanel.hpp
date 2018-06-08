#ifndef TRAJCONTROLPANEL_HPP
#define TRAJCONTROLPANEL_HPP

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QGroupBox>
#include <QListWidget>
#include <QPushButton>

#include <QMessageBox>

#include <QVector3D>

#include "stdexcept"

#include "../windows/addtrajwindow.hpp"
#include "../../sceneobj//traj.hpp"

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
    QPushButton *m_collisionButton;

    QList<Traj*> m_trajs;

    double m_minBeginTime;
    double m_maxEndTime;
    double m_minTimeStep;

    bool m_isCollisionMode;
    bool m_isCollisionComputed;

    void updateGeneralTimeValues();

    bool isCorrectIndex(int index) const;
    bool isOneTraj() const;
    bool isNoneTraj() const;

    void setTraj(Traj *traj);
    void unsetTraj(int index);

    void disableControls();
    void enableControls();

    void setTrajSeparated(bool status);

    void computeTrajCollision();
    void showTrajCollision();
    void hideTrajCollision();

    QString createTrajListName(Traj *traj) const;

private slots:
    void addTraj();
    void deleteTraj();
    void selectTraj();
    void focusTraj();
    void setTrajDisplay(QListWidgetItem *item);

    void collision();

signals:
    void trajAdded(Traj *traj);
    void trajDeleted(int pos);
    void trajFocused(Traj *traj);
    void trajSelected(Traj *traj);
    void trajUpdated();

    void generalBeginTimeChanged(double time);
    void generalEndTimeChanged(double time);
    void generalTimeStepChanged(double step);

    void firstTrajWasAdded();
    void lastTrajWasDeleted();
};

#endif // TRAJCONTROLPANEL_HPP

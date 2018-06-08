#include "trajcontrolpanel.hpp"

TrajControlPanel::TrajControlPanel(QWidget *parent)
    : QGroupBox(parent)
{
    /* Configurate list widget */
    m_trajList = new QListWidget;
    m_trajList->setFixedWidth(100);

    /* Configurate add button */
    m_addButton = new QPushButton("Add");
    m_addButton->setFixedHeight(25);
    m_addButton->setFixedWidth(60);

    /* Configurate delete button */
    m_deleteButton = new QPushButton("Delete");
    m_deleteButton->setFixedHeight(25);
    m_deleteButton->setFixedWidth(60);
    m_deleteButton->setEnabled(false);

    /* Configurate select button */
    m_selectButton = new QPushButton("Select");
    m_selectButton->setFixedHeight(25);
    m_selectButton->setFixedWidth(60);
    m_selectButton->setEnabled(false);

    /* Configurate focus button */
    m_focusButton = new QPushButton("Focus");
    m_focusButton->setFixedHeight(25);
    m_focusButton->setFixedWidth(60);
    m_focusButton->setEnabled(false);

    /* Configurate collision button */
    m_collisionButton = new QPushButton("Compute\ncollision");
    m_collisionButton->setFixedHeight(40);
    m_collisionButton->setFixedWidth(60);
    m_collisionButton->setEnabled(false);

    /* Configurate buttons layout */
    m_buttonsLayout = new QVBoxLayout;
    m_buttonsLayout->setMargin(0);
    m_buttonsLayout->addWidget(m_addButton);
    m_buttonsLayout->addWidget(m_deleteButton);
    m_buttonsLayout->addWidget(m_selectButton);
    m_buttonsLayout->addWidget(m_focusButton);
    m_buttonsLayout->addWidget(m_collisionButton);
    m_buttonsLayout->addStretch(1);

    /* Configurate main layout */
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->addWidget(m_trajList);
    m_mainLayout->addLayout(m_buttonsLayout);

    /* Configurate widget */
    setTitle("Trajectories");
    setContentsMargins(5, 15, 5, 5);
    setFixedWidth(200);
    setLayout(m_mainLayout);

    m_isCollisionMode = false;;
    m_isCollisionComputed = false;

    /* Configurate connections */
    connect(m_addButton, &QPushButton::clicked, this, &TrajControlPanel::addTraj);
    connect(m_deleteButton, &QPushButton::clicked, this, &TrajControlPanel::deleteTraj);
    connect(m_selectButton, &QPushButton::clicked, this, &TrajControlPanel::selectTraj);
    connect(m_focusButton, &QPushButton::clicked, this, &TrajControlPanel::focusTraj);
    connect(m_collisionButton, &QPushButton::clicked, this, &TrajControlPanel::collision);
    connect(m_trajList, &QListWidget::itemChanged, this, &TrajControlPanel::setTrajDisplay);
    connect(m_trajList, &QListWidget::itemDoubleClicked, this, &TrajControlPanel::selectTraj);
}

void TrajControlPanel::updateGeneralTimeValues()
{
    /* Update general begin time */
    double generalBegin = TrajUtills::computeGeneralBeginTime(m_trajs);
    emit generalBeginTimeChanged(generalBegin);

    /* Update general end time */
    double generalEnd = TrajUtills::computeGeneralEndTime(m_trajs);
    emit generalEndTimeChanged(generalEnd);

    /* Update general time step */
    double generalStep = TrajUtills::computeGeneralTimeStep(m_trajs);
    emit generalTimeStepChanged(generalStep);
}

bool TrajControlPanel::isCorrectIndex(int index) const
{
    return index >=0 && index < m_trajList->count();
}

bool TrajControlPanel::isOneTraj() const
{
    return m_trajList->count() == 1;
}

bool TrajControlPanel::isNoneTraj() const
{
    return m_trajs.empty();
}

void TrajControlPanel::setTraj(Traj *traj)
{
    /* Create name */
    QString name = createTrajListName(traj);

    /* Set into list widget */
    QListWidgetItem *item = new QListWidgetItem(name, m_trajList);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Checked);

    /* Notify */
    emit trajAdded(traj);
    if (isOneTraj()) {
        emit firstTrajWasAdded();
        emit trajFocused(traj);
    }

    /* Update */
    if (isOneTraj()) {
        enableControls();
        updateGeneralTimeValues();
    }
    m_isCollisionComputed = false;
    m_collisionButton->setText("Compute\ncollision");
}

void TrajControlPanel::unsetTraj(int index)
{
    /* Unset from traj list */
    m_trajList->takeItem(index);

    /* Notify */
    emit trajDeleted(index);
    if (isNoneTraj()) {
        emit lastTrajWasDeleted();
    }

    /* Update */
    if (isNoneTraj()) {
        disableControls();
    }
    else {
        updateGeneralTimeValues();
    }
    m_isCollisionComputed = false;
    m_collisionButton->setText("Compute\ncollision");
}

#include <QDebug>

void TrajControlPanel::addTraj()
{
    try {
        /* Open subwindow */
        AddTrajWindow *w = new AddTrajWindow(this);
        w->exec();

        /* Handle */
        if (w->result() == QDialog::Accepted) {
            Traj *traj = w->getTraj();

            m_trajs.push_back(traj);
            setTraj(traj);
        }
    }
    catch (std::exception &e) {
        QMessageBox box;
        box.setText("Incorrect data");
        box.exec();
    }
}

void TrajControlPanel::deleteTraj()
{
    /* Get index */
    int index = m_trajList->currentRow();

    /* Handle */
    if (isCorrectIndex(index)) {
        m_trajs.removeAt(index);

        unsetTraj(index);
    }
}

void TrajControlPanel::selectTraj()
{
    /* Get index */
    int index = m_trajList->currentRow();

    /* Handle */
    if (isCorrectIndex(index)) {
        emit trajSelected(m_trajs[index]);
    }
}

void TrajControlPanel::focusTraj()
{
    /* Get index */
    int index = m_trajList->currentRow();

    /* Handle */
    if (isCorrectIndex(index)) {
        emit trajFocused(m_trajs[index]);
    }
}

void TrajControlPanel::setTrajDisplay(QListWidgetItem *item)
{
    /* Get index */
    int index = m_trajList->row(item);

    /* Get display status */
    Qt::CheckState status = item->checkState();

    m_trajs.at(index)->setDisplayed(status);

    /* Notify */
    emit trajUpdated();
}

void TrajControlPanel::collision()
{
    if (m_isCollisionMode) {
        hideTrajCollision();
    }
    else {
        if (!m_isCollisionComputed) {
            computeTrajCollision();
        }

        showTrajCollision();
    }
}

void TrajControlPanel::disableControls()
{
    m_deleteButton->setEnabled(false);
    m_selectButton->setEnabled(false);
    m_focusButton->setEnabled(false);
    m_collisionButton->setEnabled(false);
}

void TrajControlPanel::enableControls()
{
    m_deleteButton->setEnabled(true);
    m_selectButton->setEnabled(true);
    m_focusButton->setEnabled(true);
    m_collisionButton->setEnabled(true);
}

void TrajControlPanel::setTrajSeparated(bool status)
{
    for (int i = 0; i < m_trajs.count(); i++) {
        m_trajs[i]->setCollisionMapped(status);
    }
}

void TrajControlPanel::computeTrajCollision()
{
    /* Compute segment index of the collision border */
    int borderSegmentIndex = TrajUtills::computeCollisionSegmentIndex(m_trajs);

    /* Set border for each trajectory */
    for (int i = 0; i < m_trajs.count(); i++) {
        m_trajs[i]->setTimeBorderAtSegment(borderSegmentIndex);
    }

    /* Update flags */
    m_isCollisionComputed = true;
}

void TrajControlPanel::showTrajCollision()
{
    setTrajSeparated(true);

    m_isCollisionMode = true;
    m_collisionButton->setText("Hide\ncollision");

    emit trajUpdated();
}

void TrajControlPanel::hideTrajCollision()
{
    setTrajSeparated(false);

    m_isCollisionMode = false;
    m_collisionButton->setText("Show\ncollision");

    emit trajUpdated();
}

QString TrajControlPanel::createTrajListName(Traj *traj) const
{
    QString name = traj->getName();
    QString initials = traj->getStringInitials();

    return name + initials;
}

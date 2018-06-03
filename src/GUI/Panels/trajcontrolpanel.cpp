#include "trajcontrolpanel.hpp"

#include <QDebug>

TrajControlPanel::TrajControlPanel(QWidget *parent)
    : QGroupBox(parent)
{
    /* Configurate list widget */
    m_trajList = new QListWidget;
    m_trajList->setFixedWidth(80);

    /* Configurate add button */
    m_addButton = new QPushButton("Add");
    m_addButton->setFixedHeight(25);
    m_addButton->setFixedWidth(40);

    /* Configurate delete button */
    m_deleteButton = new QPushButton("Delete");
    m_deleteButton->setFixedHeight(25);
    m_deleteButton->setFixedWidth(40);

    /* Configurate select button */
    m_selectButton = new QPushButton("Edit");
    m_selectButton->setFixedHeight(25);
    m_selectButton->setFixedWidth(40);

    /* Configurate focus button */
    m_focusButton = new QPushButton("Focus");
    m_focusButton->setFixedHeight(25);
    m_focusButton->setFixedWidth(40);

    /* Configurate show collision button */
    m_showCollisionButton = new QPushButton("Show Collision");
    m_showCollisionButton->setFixedHeight(25);
    m_showCollisionButton->setFixedWidth(40);
    m_showCollisionButton->setEnabled(false);

    /* Configurate show collision button */
    m_hideCollisionButton = new QPushButton("Hide Collision");
    m_hideCollisionButton->setFixedHeight(25);
    m_hideCollisionButton->setFixedWidth(40);
    m_hideCollisionButton->setEnabled(false);

    /* Configurate buttons layout */
    m_buttonsLayout = new QVBoxLayout;
    m_buttonsLayout->setMargin(0);
    m_buttonsLayout->addWidget(m_addButton);
    m_buttonsLayout->addWidget(m_deleteButton);
    m_buttonsLayout->addWidget(m_selectButton);
    m_buttonsLayout->addWidget(m_focusButton);
    m_buttonsLayout->addWidget(m_showCollisionButton);
    m_buttonsLayout->addWidget(m_hideCollisionButton);
    m_buttonsLayout->addStretch(1);

    /* Configurate main layout */
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->addWidget(m_trajList);
    m_mainLayout->addLayout(m_buttonsLayout);

    /* Configurate widget */
    setTitle("Trajectories");
    setContentsMargins(5, 15, 5, 5);
    setFixedWidth(150);
    setLayout(m_mainLayout);

    /* Configurate connections */
    connect(m_addButton, &QPushButton::clicked, this, &TrajControlPanel::addTraj);
    connect(m_deleteButton, &QPushButton::clicked, this, &TrajControlPanel::deleteTraj);
    connect(m_selectButton, &QPushButton::clicked, this, &TrajControlPanel::selectTraj);
    connect(m_focusButton, &QPushButton::clicked, this, &TrajControlPanel::focusTraj);
    connect(m_trajList, &QListWidget::itemChanged, this, &TrajControlPanel::setTrajDisplay);
    connect(m_trajList, &QListWidget::itemDoubleClicked, this, &TrajControlPanel::selectTraj);
    connect(m_showCollisionButton, &QPushButton::clicked, this, &TrajControlPanel::showCollision);
    connect(m_hideCollisionButton, &QPushButton::clicked, this, &TrajControlPanel::hideCollision);
}

void TrajControlPanel::updateGeneralTimeValues()
{
    /* Update general begin time */
    double generalBegin = TrajUtills::compGeneralBeginTime(m_trajs);
    emit generalBeginTimeChanged(generalBegin);

    /* Update general end time */
    double generalEnd = TrajUtills::compGeneralEndTime(m_trajs);
    emit generalEndTimeChanged(generalEnd);

    /* Update general time step */
    double generalStep = TrajUtills::compGeneralTimeStep(m_trajs);
    emit generalTimeStepChanged(generalStep);
}

bool TrajControlPanel::checkIndex(int index) const
{
    return index >= 0 && index < m_trajList->count();
}

bool TrajControlPanel::checkFirst() const
{
    return m_trajs.count() == 1;
}

bool TrajControlPanel::checkLast() const
{
    return m_trajs.empty();
}

void TrajControlPanel::addTraj()
{
    AddTrajWindow *w = new AddTrajWindow(this);
    w->exec();

    if (w->result() == QDialog::Accepted) {
        /* Load traj */
        Traj *traj = w->getTraj();

        /* Add traj */
        m_trajs.push_back(traj);

        /* Add traj to list widget */
        QListWidgetItem *item = new QListWidgetItem(traj->getName(), m_trajList);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);

        /* Notify about current state */
        if (checkFirst()) {
            emit firstTrajWasAdded(traj);
            emit trajFocused(traj);

            m_showCollisionButton->setEnabled(true);
        }
        updateGeneralTimeValues();

        emit trajAdded(traj);
    }
}

void TrajControlPanel::deleteTraj()
{
    int row = m_trajList->currentRow();
    if (checkIndex(row)) {
        /* Delete traj */
        m_trajs.removeAt(row);

        /* Delete from the list widget */
        m_trajList->takeItem(row);

        /* Notify about current state */
        if (checkLast()) {
            emit allTrajWasDeleted();

            m_showCollisionButton->setEnabled(false);
        }
        else {
            updateGeneralTimeValues();
        }

        emit trajDeleted(row);
    }
}

void TrajControlPanel::selectTraj()
{
    int row = m_trajList->currentRow();
    if (checkIndex(row)) {
        emit trajSelected(m_trajs.at(row));
    }
}

void TrajControlPanel::focusTraj()
{
    int row = m_trajList->currentRow();
    if (checkIndex(row)) {
        emit trajFocused(m_trajs.at(row));
    }
}

void TrajControlPanel::setTrajDisplay(QListWidgetItem *item)
{
    int row = m_trajList->row(item);
    Qt::CheckState status = item->checkState();

    m_trajs.at(row)->setDisplayed(status);
    emit trajUpdated();
}

void TrajControlPanel::showCollision()
{
    /* Update traj */
    int borderSegmentIndex = TrajUtills::compGeneralCollisionTimeBorder(m_trajs);
    for (int i = 0; i < m_trajs.count(); i++) {
        m_trajs[i]->setTimeBorderAtSegment(borderSegmentIndex);
        m_trajs[i]->setCollisionMapped(true);
    }
    emit trajUpdated();

    /* Update widgets */
    m_showCollisionButton->setEnabled(false);
    m_hideCollisionButton->setEnabled(true);
}

void TrajControlPanel::hideCollision()
{
    /* Update trajectories */
    for (int i = 0; i < m_trajs.count(); i++) {
        m_trajs[i]->setCollisionMapped(false);
    }
    emit trajUpdated();

    /* Update widgets */
    m_showCollisionButton->setEnabled(true);
    m_hideCollisionButton->setEnabled(false);
}

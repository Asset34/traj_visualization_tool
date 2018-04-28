#include "trajpanel.hpp"

TrajPanel::TrajPanel(QWidget *parent)
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

    /* Configurate edit button */
    m_editButton = new QPushButton("Edit");
    m_editButton->setFixedHeight(25);
    m_editButton->setFixedWidth(40);

    /* Configurate focus button */
    m_focusButton = new QPushButton("Focus");
    m_focusButton->setFixedHeight(25);
    m_focusButton->setFixedWidth(40);

    /* Configurate buttons layout */
    m_buttonsLayout = new QVBoxLayout;
    m_buttonsLayout->setMargin(0);
    m_buttonsLayout->addWidget(m_addButton);
    m_buttonsLayout->addWidget(m_deleteButton);
    m_buttonsLayout->addWidget(m_editButton);
    m_buttonsLayout->addWidget(m_focusButton);
    m_buttonsLayout->addStretch(1);

    /* Configurate main layout */
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->addWidget(m_trajList);
    m_mainLayout->addLayout(m_buttonsLayout);

    /* Configurate widget */
    setLayout(m_mainLayout);
    setTitle("Trajectories");
    setContentsMargins(5, 15, 5, 5);
    setFixedWidth(150);

    /* Configurate connections */
    connect(m_addButton, &QPushButton::clicked, this, &TrajPanel::addTraj);
    connect(m_deleteButton, &QPushButton::clicked, this, &TrajPanel::deleteTraj);
    connect(m_editButton, &QPushButton::clicked, this, &TrajPanel::editTraj);
    connect(m_focusButton, &QPushButton::clicked, this, &TrajPanel::focusTraj);
    connect(m_trajList, &QListWidget::itemChanged, this, &TrajPanel::setDisplayStatus);
}

void TrajPanel::addTraj()
{
    AddTrajWindow *w = new AddTrajWindow(this);
    w->exec();

    if (w->result() == QDialog::Accepted) {
        /* Load traj */
        Traj *traj = w->getTraj();

        updateTimeBorders(traj);

        /* Add traj */
        m_trajs.push_back(traj);

        /* Add traj to list widget */
        QListWidgetItem *item = new QListWidgetItem(convertInitials(traj->getInitials()),
                                                    m_trajList);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);

        emit trajAdded(traj);
    }
}

void TrajPanel::deleteTraj()
{
    int row = m_trajList->currentRow();

    if (row >= 0 && row < m_trajs.count()) {
        /* Delete traj */
        m_trajs.removeAt(row);

        /* Delete from the list widget */
        m_trajList->takeItem(row);

        emit trajDeleted(row);
    }
}

void TrajPanel::editTraj()
{
    int row = m_trajList->currentRow();

    if (row >= 0 && row < m_trajs.count()) {
        // TODO
    }
}

void TrajPanel::focusTraj()
{
    int row = m_trajList->currentRow();

    if (row >= 0 && row < m_trajs.count()) {
        emit trajFocused(m_trajs.at(row));
    }
}

void TrajPanel::setDisplayStatus(QListWidgetItem *item)
{
    int row = m_trajList->row(item);
    Qt::CheckState status = item->checkState();

    m_trajs.at(row)->setDisplayStatus(status);

    emit trajDisplayStatusChanged();
}

QString TrajPanel::convertInitials(const QVector3D &initials)
{
    QString str;

    str.append(QString::number(initials.x()) + ", ");
    str.append(QString::number(initials.y()) + ", ");
    str.append(QString::number(initials.z()));

    return str;
}

void TrajPanel::updateTimeBorders(Traj *traj)
{
    /* Get current time values */
    int trajCount = m_trajList->count();
    double beginTime = traj->getBeginTime();
    double endTime = traj->getEndTime();
    double timeStep = traj->getTimeStep();

    /* Update */
    if (beginTime < m_minBeginTime || trajCount == 0) {
        m_minBeginTime = beginTime;
        emit trajMinBeginTimeChanged(m_minBeginTime);
    }
    if (endTime > m_maxEndTime || trajCount == 0) {
        m_maxEndTime = endTime;
        emit trajMaxEndTimeCHanged(m_maxEndTime);
    }
    if (timeStep < m_minTimeStep || trajCount == 0) {
        m_minTimeStep = timeStep;
        emit trajMinTimeStepChanged(m_minTimeStep);
    }
}

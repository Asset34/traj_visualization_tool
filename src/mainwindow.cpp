#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    /* Widgets */

    m_attractor = new OGLAttractor;
    m_attractor->setMinimumHeight(300);
    m_attractor->setMinimumWidth(300);

    m_trajsView = new QListView;
    m_trajsView->setFixedWidth(100);
    m_trajsView->setMinimumHeight(250);

    m_addButton = new QPushButton("Add");
    m_addButton->setFixedHeight(25);

    m_delButton = new QPushButton("Del");
    m_delButton->setFixedHeight(25);

    /* Layouts */

    m_controlLayout = new QVBoxLayout;
    m_controlLayout->addWidget(m_trajsView);
    m_controlLayout->addWidget(m_addButton);
    m_controlLayout->addWidget(m_delButton);

    m_mainLayout = new QHBoxLayout;
    m_mainLayout->addWidget(m_attractor);
    m_mainLayout->addLayout(m_controlLayout);

    /* Configure window */

    setWindowTitle("Attractor Visualizer");
    setLayout(m_mainLayout);
}

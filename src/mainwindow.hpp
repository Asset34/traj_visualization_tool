#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListView>

#include "oglattractor.hpp"
#include "fileutills.hpp"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QHBoxLayout *m_mainLayout;
    QVBoxLayout *m_controlLayout;

    OGLAttractor *m_attractor;
    QListView *m_trajsView;
    QPushButton *m_addButton;
    QPushButton *m_delButton;

signals:

public slots:
};

#endif // MAINWINDOW_HPP

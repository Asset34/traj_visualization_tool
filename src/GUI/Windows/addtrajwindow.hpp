#ifndef TRAJWINDOW_HPP
#define TRAJWINDOW_HPP

#include <QDialog>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

#include "../../Opengl/traj.hpp"
#include "../Boxes/openfilebox.hpp"
#include "../Panels/trajsettingspanel.hpp"

class AddTrajWindow : public QDialog
{
    Q_OBJECT

public:
    AddTrajWindow(QWidget *parent = nullptr);

    Traj *getTraj() const;

private:
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_buttonsLayout;
    OpenFileBox *m_pathBox;
    TrajSettingsPanel *m_settingsPanel;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
};

#endif // TRAJWINDOW_HPP

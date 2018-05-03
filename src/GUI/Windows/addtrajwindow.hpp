#ifndef TRAJWINDOW_HPP
#define TRAJWINDOW_HPP

#include <QDialog>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

#include "../boxes/openfilebox.hpp"
#include "../boxes/textinputbox.hpp"
#include "../../sceneobj/traj.hpp"

class AddTrajWindow : public QDialog
{
    Q_OBJECT

public:
    AddTrajWindow(QWidget *parent = nullptr);

    Traj *getTraj() const;

private:
    QHBoxLayout *m_mainLayout;
    QVBoxLayout *m_inputLayout;
    QVBoxLayout *m_buttonsLayout;
    TextInputBox *m_nameBox;
    OpenFileBox *m_pathBox;
    OpenFileBox *m_pathSectionBox;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
};

#endif // TRAJWINDOW_HPP

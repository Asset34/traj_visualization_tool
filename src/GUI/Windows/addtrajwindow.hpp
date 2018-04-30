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
#include "../Boxes/textinputbox.hpp"

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
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
};

#endif // TRAJWINDOW_HPP

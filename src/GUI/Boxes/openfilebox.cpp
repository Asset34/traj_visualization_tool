#include "openfilebox.hpp"

OpenFileBox::OpenFileBox(const QString &name,
                         const QString &directory,
                         const QString &filter,
                         QWidget *parent)
    : AbstractBox(name, parent),
      m_directory(directory),
      m_filter(filter)
{
    /* Configurate text edit */
    m_pathTextEdit = new QTextEdit;
    m_pathTextEdit->setFixedHeight(25);
    m_pathTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pathTextEdit->setLineWrapMode(QTextEdit::NoWrap);

    /* Configurate button */
    m_fileDialogButton = new QPushButton("...");
    m_fileDialogButton->setFixedWidth(50);
    m_fileDialogButton->setFixedHeight(25);

    /* Configurate layout */
    m_layout = new QHBoxLayout;
    m_layout->setMargin(0);
    m_layout->addWidget(m_pathTextEdit);
    m_layout->addWidget(m_fileDialogButton);

    /* Configurate widget */
    setFixedHeight(50);
    setContentsMargins(5, 5, 5, 0);
    setLayout(m_layout);

    /* Set connections */
    connect(m_fileDialogButton, &QPushButton::clicked, this, &OpenFileBox::setPath);
}

const QString &OpenFileBox::getDirectory() const
{
    return m_directory;
}

void OpenFileBox::setDirectory(const QString &directory)
{
    m_directory = directory;
}

const QString &OpenFileBox::getFilter() const
{
    return m_filter;
}

void OpenFileBox::setFilter(const QString &filter)
{
    m_filter = filter;
}

QString OpenFileBox::getPath() const
{
    return m_pathTextEdit->toPlainText();
}

void OpenFileBox::setPath()
{
    QString path = QFileDialog::getOpenFileName(this, "Open file", m_directory, m_filter);

    m_pathTextEdit->setText(path);

    emit pathChanged(path);
}

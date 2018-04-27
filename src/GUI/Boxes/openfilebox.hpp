#ifndef OPENFILEBOX_HPP
#define OPENFILEBOX_HPP

#include <QHBoxLayout>

#include <QGroupBox>
#include <QTextEdit>
#include <QPushButton>

#include <QFileDialog>

class OpenFileBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit OpenFileBox(const QString &name = QString(),
                         const QString &directory = QString(),
                         const QString &filter = QString(),
                         QWidget *parent = nullptr);

    QString getName() const;
    void setName(const QString &name);

    const QString &getDirectory() const;
    void setDirectory(const QString &directory);

    const QString &getFilter() const;
    void setFilter(const QString &filter);

    QString getPath() const;

private:
    QHBoxLayout *m_layout;
    QTextEdit *m_pathTextEdit;
    QPushButton *m_fileDialogButton;

    QString m_directory;
    QString m_filter;

private slots:
    void setPath();

signals:
    void pathChanged(const QString &path);

};

#endif // OPENFILEBOX_HPP

#ifndef TEXTINPUTBOX_HPP
#define TEXTINPUTBOX_HPP

#include <QHBoxLayout>

#include <QTextEdit>

#include "simpleabstractbox.hpp"

class TextInputBox : public SimpleAbstractBox
{
    Q_OBJECT

public:
    explicit TextInputBox(const QString &name = QString(),
                          QWidget *parent = nullptr);

    QString getText() const;

public slots:
    void setText(const QString &text);

private:
    QHBoxLayout *m_layout;
    QTextEdit *m_textTextEdit;

signals:
    void textChanged();

};

#endif // TEXTINPUTBOX_HPP

#include "textinputbox.hpp"

TextInputBox::TextInputBox(const QString &name, QWidget *parent)
    : SimpleAbstractBox(name, parent)
{
    /* Configurate text edit */
    m_textTextEdit = new QTextEdit;

    /* Configurate layout */
    m_layout = new QHBoxLayout;
    m_layout->setMargin(0);
    m_layout->addWidget(m_nameLabel);
    m_layout->addWidget(m_textTextEdit);

    /* Configurate widget */
    setLayout(m_layout);
    setFixedHeight(25);

    /* Set connections */
    connect(m_textTextEdit, &QTextEdit::textChanged, this, &TextInputBox::textChanged);
}

QString TextInputBox::getText() const
{
    return m_textTextEdit->toPlainText();
}

void TextInputBox::setText(const QString &text)
{
    m_textTextEdit->setText(text);
}

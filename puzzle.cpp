#include "puzzle.h"

Puzzle::Puzzle(const QString &text, QWidget *parent) : QToolButton (parent)
{
    this->setToolButtonStyle(Qt::ToolButtonIconOnly);
    this->setText(text);
    label = new QLabel(text, this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("QLabel { color : red; }");
}

Puzzle::~Puzzle()
{

}

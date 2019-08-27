#include "puzzle.h"

Puzzle::Puzzle(const QString &text, QWidget *parent) : QToolButton(parent)
{
    this->setToolButtonStyle(Qt::ToolButtonIconOnly);
    this->setText(text);
    label = new QLabel(text, this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("QLabel { color : red; }");
}

Puzzle::Puzzle(const Puzzle &puzzle, QWidget *parent, int level)
{
    Puzzle(puzzle.text(), parent);

    resize(puzzle.size());
    getLabel()->resize(puzzle.size());
    //getLabel()->setFont(puzzle.font());
    //setIcon(puzzle.icon());
    //setIconSize(puzzle.iconSize());

    move(puzzle.pos().x() + puzzle.width()*level + 20, puzzle.pos().y());
}

Puzzle::~Puzzle()
{

}

QLabel* Puzzle::getLabel()
{
    return label;
}

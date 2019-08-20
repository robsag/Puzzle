#ifndef PUZZLE_H
#define PUZZLE_H

#include <QToolButton>
#include <QLabel>

class Puzzle : public QToolButton
{

public:
    Puzzle(const QString&, QWidget*);
    ~Puzzle();
    QLabel *label;

};

#endif // PUZZLE_H

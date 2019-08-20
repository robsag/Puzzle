#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <puzzle.h>

class GameBoard
{

public:
    GameBoard(int, QWidget*);
    ~GameBoard();
    Puzzle* getPuzzle(int);
    Puzzle* getPuzzleByPos(const QPoint&);
    void setPuzzlePos(int, const QPoint&);
    int getSize(void);
    void display(void);

private:
    std::vector<Puzzle*> *puzzles;

};

#endif // GAMEBOARD_H

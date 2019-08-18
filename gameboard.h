#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <puzzle.h>

class GameBoard
{

public:
    GameBoard(int, QWidget*);
    ~GameBoard();
    void getPuzzle(Puzzle*);
    void display(void);

private:
    std::vector<Puzzle*> *puzzles;

};

#endif // GAMEBOARD_H

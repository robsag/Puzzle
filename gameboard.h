#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <puzzle.h>

class GameBoard
{
private:
    std::vector<std::vector<Puzzle>> puzzles;

public:
    GameBoard();
    void getPuzzle(Puzzle*);
};

#endif // GAMEBOARD_H

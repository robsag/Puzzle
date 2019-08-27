#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <puzzle.h>

class GameBoard
{

public:
    GameBoard(int, QWidget*);
    GameBoard(const GameBoard&, QWidget*);
    ~GameBoard();
    std::vector<Puzzle*>* getPuzzles();
    Puzzle* getPuzzle(int);
    Puzzle* getPuzzleByPos(const QPoint&);
    void setPuzzlePos(int, const QPoint&);
    int getSize(void);
    void display(void);
    bool isSolved(void);

private:
    std::vector<Puzzle*> *puzzles;
    std::vector<int> sollution;
    std::vector<int> *placement;

};

#endif // GAMEBOARD_H

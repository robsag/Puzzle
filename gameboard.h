#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <puzzle.h>

using namespace std;

class GameBoard
{
public:
    GameBoard(int, QWidget*);
    GameBoard(const GameBoard&, QWidget*);
    ~GameBoard();
    vector<Puzzle*>* getPuzzles();
    Puzzle* getPuzzle(int);
    Puzzle* getPuzzleByPos(const QPoint&);
    void setPuzzlePos(int, const QPoint&);
    vector<int>* getSollution(void);
    vector<int>* getPlacement(void);
    bool isSolved(void);
    void display(void);

private:
    vector<Puzzle*> *puzzles;
    vector<int> *sollution;
    vector<int> *placement;
};

#endif // GAMEBOARD_H

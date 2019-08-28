#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <gameboard.h>

using namespace std;

class Player
{
public:
    Player();
    virtual ~Player();
    string getName(void);
    virtual void movePuzzle(GameBoard*, QToolButton* = nullptr) = 0;

protected:
    string name;
};

#endif // PLAYER_H

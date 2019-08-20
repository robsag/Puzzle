#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <gameboard.h>

class Player
{

public:
    Player();
    virtual ~Player();
    std::string getName(void);
    virtual void movePuzzle(QToolButton*, GameBoard*) = 0;

protected:
    std::string name;

};

#endif // PLAYER_H

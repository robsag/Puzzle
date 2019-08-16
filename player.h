#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
    std::string name;
public:
    Player();
    virtual ~Player();
    std::string getName(void);
    virtual void movePuzzle(int, int) = 0;
};

#endif // PLAYER_H

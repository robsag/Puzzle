#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <player.h>

class HumanPlayer : public Player
{
public:
    HumanPlayer();
    ~HumanPlayer();
    void movePuzzle(int, int);
};

#endif // HUMANPLAYER_H

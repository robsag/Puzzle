#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <player.h>

class HumanPlayer : public Player
{
public:
    HumanPlayer(string);
    ~HumanPlayer();
    void movePuzzle(GameBoard*, QToolButton*);
};

#endif // HUMANPLAYER_H

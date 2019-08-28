#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <player.h>

class ComputerPlayer : public Player
{
public:
    ComputerPlayer();
    ~ComputerPlayer();
    void movePuzzle(GameBoard*, QToolButton*);
};

#endif // COMPUTERPLAYER_H

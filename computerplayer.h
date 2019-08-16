#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <player.h>

class ComputerPlayer : public Player
{
public:
    ComputerPlayer();
    ~ComputerPlayer();
    void movePuzzle(int, int);
};

#endif // COMPUTERPLAYER_H

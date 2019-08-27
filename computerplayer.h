#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <player.h>

class ComputerPlayer : public Player
{
public:
    ComputerPlayer();
    ~ComputerPlayer();
    void movePuzzle(QToolButton*, GameBoard*);
};

#endif // COMPUTERPLAYER_H

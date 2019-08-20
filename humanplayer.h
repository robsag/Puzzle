#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <player.h>

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string);
    ~HumanPlayer();
    void movePuzzle(QToolButton*, GameBoard*);

};

#endif // HUMANPLAYER_H

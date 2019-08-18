#ifndef GAME_H
#define GAME_H

#include <string>
#include <gameboard.h>
#include <player.h>

class Game
{
public:
    Game (QWidget*);
    Game(std::string);
    ~Game();
    int getTime(void);
    void setTime(int);
    void play(void);
    void load(void);
    void save(void);

private:
    GameBoard *gameBoard;
    Player *player;
    int time;

};

#endif // GAME_H

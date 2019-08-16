#ifndef GAME_H
#define GAME_H

#include <string>
#include <player.h>

class Game
{
private:
    Player *player;
    int time;

public:
    Game ();
    Game(std::string);
    ~Game();
    int getTime(void);
    void setTime(int);
    void play(void);
    void load(void);
    void save(void);
};

#endif // GAME_H

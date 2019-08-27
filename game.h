#ifndef GAME_H
#define GAME_H

#include <string>
#include <gameboard.h>
#include <player.h>
#include <mainwindow.h>

class Game : public QObject
{
public:
    Game (QWidget*, QString, int, bool = true);
    Game(std::string);
    ~Game();
    GameBoard* getGameBoard1(void);
    GameBoard* getGameBoard2(void);
    Player* getPlayer1(void);
    Player* getPlayer2(void);
    int getTime(void);
    void setTime(int);
    void play(void);
    void load(void);
    void save(void);

private:
    GameBoard *gameBoard1;
    GameBoard *gameBoard2;
    Player *player1;
    Player *player2;
    int time;

};

#endif // GAME_H

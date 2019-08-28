#ifndef GAME_H
#define GAME_H

#include <string>
#include <gameboard.h>
#include <player.h>
#include <mainwindow.h>

using namespace std;

class Game : public QObject
{
public:
    Game(QWidget*, QString, int, bool = true);
    Game(QWidget *parent, string);
    ~Game();
    GameBoard* getGameBoard(int = 1);
    Player* getPlayer(int = 1);
    int getTime(void);
    void setTime(int);
    void play(void);
    void save(void);
    void disable(void);

private:
    GameBoard *gameBoard1;
    GameBoard *gameBoard2;
    Player *player1;
    Player *player2;
    int time;
};

#endif // GAME_H

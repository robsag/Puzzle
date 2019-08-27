#include "game.h"
#include "humanplayer.h"
#include "computerplayer.h"

Game::Game(QWidget *parent, QString playerName, int level, bool singleplayer)
{
    time = 0;
    gameBoard1 = new GameBoard(level, parent);
    gameBoard1->display();

    player1 = new HumanPlayer(playerName.toStdString());

    if(singleplayer) {
        player2 = nullptr;
        gameBoard2 = nullptr;
    } else {
        player2 = new ComputerPlayer();
        gameBoard2 = new GameBoard(*gameBoard1, parent);
    }

    for (int i = 0; i < pow(level,2); i++) {
        connect(gameBoard1->getPuzzle(i), SIGNAL(clicked()), parent, SLOT(on_click_toolButton()));
    }
}

Game::Game(std::string file)
{
    //time = ?;
}

Game::~Game()
{
    delete player1;
    delete player2;
    delete gameBoard1;
    delete gameBoard2;
}

GameBoard *Game::getGameBoard1()
{
    return gameBoard1;
}

GameBoard *Game::getGameBoard2()
{
    return gameBoard2;
}

Player *Game::getPlayer1()
{
    return player1;
}

Player *Game::getPlayer2()
{
    return player2;
}

int Game::getTime(void)
{
    return time;
}

void Game::setTime(int time)
{
    this->time = time;
}

void Game::play()
{

}

void Game::load()
{

}

void Game::save()
{

}

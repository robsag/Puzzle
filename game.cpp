#include "game.h"
#include "humanplayer.h"
#include "computerplayer.h"

Game::Game(QWidget *parent)
{
    int level = 3;

    time = 0;
    gameBoard = new GameBoard(level, parent); //TODO: gameboard size
    gameBoard->display();

    player = new HumanPlayer("tester");

    for (int i = 0; i < pow(level,2); i++) {
        connect(gameBoard->getPuzzle(unsigned(i)), SIGNAL(clicked()), parent, SLOT(on_click_toolButton(/*gameBoard->getPuzzle(unsigned(i))*/)));
    }
}

Game::Game(std::string file)
{
    //time = ?;
}

Game::~Game()
{
    delete player;
    delete gameBoard;
}

GameBoard *Game::getGameBoard()
{
    return gameBoard;
}

Player *Game::getPlayer()
{
    return player;
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

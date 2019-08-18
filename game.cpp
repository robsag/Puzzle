#include "game.h"

Game::Game(QWidget *parent)
{
    time = 0;
    gameBoard = new GameBoard(3, parent); //TODO: gameboard size
    gameBoard->display();
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

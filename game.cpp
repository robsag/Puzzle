#include "game.h"

Game::Game()
{
    time = 0;
}

Game::Game(std::string file)
{
    //time = ?;
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

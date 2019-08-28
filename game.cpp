#include <fstream>
#include "game.h"
#include "humanplayer.h"
#include "computerplayer.h"

Game::Game(QWidget *parent, QString playerName, int level, bool singleplayer)
{
    time = 0;
    gameBoard1 = new GameBoard(level, parent);

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

Game::Game(QWidget *parent, string file)
{
    ifstream gameSave(file, ofstream::out);
    string buff;

    getline(gameSave, buff);
    player1 = new HumanPlayer(buff);

    getline(gameSave, buff);
    int level = stoi(buff);

    getline(gameSave, buff);
    time = stoi(buff);

    getline(gameSave, buff);
    bool singleplayer = stoi(buff) == 1? true : false;

    vector<int> placement1;
    while (getline(gameSave, buff, ' ')) {
        placement1.push_back(stoi(buff)); //exception - poprawić
    }

    /*gameBoard1 = new GameBoard(level, parent);

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
    }*/
}

Game::~Game()
{
    delete player1;
    delete player2;
    delete gameBoard1;
    delete gameBoard2;

    remove("zapis.txt");
}

GameBoard *Game::getGameBoard(int gameBoard)
{
    switch (gameBoard) {
    case 2:
        return gameBoard2;
    default:
        return gameBoard1;
    }
}

Player *Game::getPlayer(int player)
{
    switch (player) {
    case 2:
        return player2;
    default:
        return player1;
    }
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
    gameBoard1->display();
    if (gameBoard2 != nullptr) {
        gameBoard2->display();
    }
}

void Game::save()
{
    ofstream gameSave("zapis", ofstream::out);

    gameSave << player1->getName() << endl;
    gameSave << sqrt(getGameBoard()->getPuzzles()->size()) << endl;
    gameSave << time << endl;
    gameBoard2 == nullptr? gameSave << 1 << endl : gameSave << 2 << endl;

    for (int place : *getGameBoard()->getPlacement()) {
        gameSave << place << " ";
    }
    gameSave << endl;

    if (getGameBoard(2) != nullptr) {
        for (int place : *getGameBoard(2)->getPlacement()) {
            gameSave << place << " ";
        }
        gameSave << endl;
    }

    if (getGameBoard(2) != nullptr) {
        for (int step : *getGameBoard(2)->getSollution()) {
            gameSave << step << " ";
        }
    }

    gameSave.close();
}

void Game::disable(void)
{
    for (int i = 0; i < int(getGameBoard()->getPuzzles()->size()) - 1; i++) {
        (*getGameBoard()->getPuzzles())[unsigned(i)]->setEnabled(false);
    }

    if (getGameBoard(2) != nullptr) {
        for (int i = 0; i < int(getGameBoard()->getPuzzles()->size()) - 1; i++) {
            (*getGameBoard(2)->getPuzzles())[unsigned(i)]->setEnabled(false);
        }
    }
}

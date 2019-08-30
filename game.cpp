#include <fstream>
#include <sstream>
#include "game.h"
#include "humanplayer.h"
#include "computerplayer.h"

template <typename T> void filePrint(string, T);

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
    getline(gameSave, buff);
    istringstream _placement1(buff);
    for (int i = 0; i < pow(level, 2); i++) {
        int place;
        _placement1 >> place;
        placement1.push_back(place);
    }
    gameBoard1 = new GameBoard(level, parent, placement1);

    if(singleplayer) {
        player2 = nullptr;
        gameBoard2 = nullptr;
    } else {
        player2 = new ComputerPlayer();

        vector<int> placement2;
        getline(gameSave, buff);
        istringstream _placement2(buff);
        for (int i = 0; i < pow(level, 2); i++) {
            int place;
            _placement2 >> place;
            placement2.push_back(place);
        }
        gameBoard2 = new GameBoard(level, parent, placement2, singleplayer);

        getline(gameSave, buff);
        istringstream _sollution(buff);
        int step;
        _sollution >> step;
        do {
            gameBoard2->getSollution()->push_back(step);
            _sollution >> step;
        } while (_sollution);
    }

    for (int i = 0; i < pow(level,2); i++) {
        connect(gameBoard1->getPuzzle(i), SIGNAL(clicked()), parent, SLOT(on_click_toolButton()));
    }
}

Game::~Game()
{
    delete player1;
    delete player2;
    delete gameBoard1;
    delete gameBoard2;
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
    ofstream ofs("zapis", ofstream::out);

    filePrint("zapis", player1->getName());
    filePrint("zapis", "\n");

    filePrint("zapis", sqrt(getGameBoard()->getPuzzles()->size()));
    filePrint("zapis", "\n");

    filePrint("zapis", time);
    filePrint("zapis", "\n");

    if (gameBoard2 == nullptr) {
        filePrint("zapis", 1);
    } else {
        filePrint("zapis", 2);
    }
    filePrint("zapis", "\n");

    for (int place : *getGameBoard()->getPlacement()) {
        filePrint("zapis", place);
        filePrint("zapis", " ");
    }
    filePrint("zapis", "\n");

    if (getGameBoard(2) != nullptr) {
        for (int place : *getGameBoard(2)->getPlacement()) {
            filePrint("zapis", place);
            filePrint("zapis", " ");
        }
        filePrint("zapis", "\n");
    }

    if (getGameBoard(2) != nullptr) {
        for (int step : *getGameBoard(2)->getSollution()) {
            filePrint("zapis", step);
            filePrint("zapis", " ");
        }
    }
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

template <typename T> void filePrint(string filename, T data) {
    ofstream ofs(filename, ofstream::app);
    ofs << data;
    ofs.close();
}

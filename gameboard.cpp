#include <algorithm>
#include <random>
#include "gameboard.h"
#include "puzzle.h"

GameBoard::GameBoard(int size, QWidget *parent)
{
    //inicjalizacja puzzli
    puzzles = new std::vector<Puzzle*>(pow(size,2));
    int puzzleSize = (parent->size().width() - 40)/size;
    int x = puzzleSize;
    for (int i = 0; i < pow(size,2) - 1; i++) {
        Puzzle* newPuzzle = new Puzzle(QString::fromStdString(std::to_string(i + 1)), parent);
        newPuzzle->resize(puzzleSize,puzzleSize);
        newPuzzle->label->resize(puzzleSize,puzzleSize);
        newPuzzle->label->setFont(QFont("Snap ITC", newPuzzle->width() / 8));
        (*puzzles)[i] = newPuzzle;
    }

    //ustawianie tła puzzli
    QPixmap puzzleBackground(":/PuzzleBackground/gg_pw.jpg");
    int rectWidth = puzzleBackground.width()/size;
    int rectHeight = puzzleBackground.height()/size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((*puzzles)[i*size + j] != nullptr) {
                QRect rect(rectWidth * i, rectHeight * j, puzzleSize - 10, puzzleSize - 10);
                QPixmap croppedBackground = puzzleBackground.copy(rect);
                QIcon buttonBackground(croppedBackground);
                (*puzzles)[j*size + i]->setIcon(croppedBackground);
                (*puzzles)[j*size + i]->setIconSize(croppedBackground.rect().size());
            }
        }
    }

    //mieszanie puzzli
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(puzzles->begin(), puzzles->end(), g);

    //ustawienie pozycji puzzli
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((*puzzles)[j*size + i] != nullptr) {
                (*puzzles)[j*size + i]->move(20 + i*puzzleSize, 40 + j*puzzleSize);
            }
        }
    }
}

GameBoard::~GameBoard()
{
    for (Puzzle *puzzle : *puzzles) {
        delete puzzle;
    }
    puzzles->clear();
}

void GameBoard::getPuzzle(Puzzle * puzzle)
{

}

void GameBoard::display()
{
    for (int i = 0; i < int(puzzles->size()); i++) {
        if ((*puzzles)[i] != nullptr) {
            (*puzzles)[i]->show();
        }
    }
}

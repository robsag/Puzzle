#include <algorithm>
#include <random>
#include "gameboard.h"
#include "puzzle.h"

GameBoard::GameBoard(int size, QWidget *parent)
{
    //inicjalizacja puzzli
    puzzles = new std::vector<Puzzle*>(unsigned(pow(size,2)));
    int puzzleSize = (parent->size().width() - 40)/size;
    for (int i = 0; i < pow(size,2) - 1; i++) {
        Puzzle* newPuzzle = new Puzzle(QString::fromStdString(std::to_string(i + 1)), parent);
        newPuzzle->resize(puzzleSize,puzzleSize);
        newPuzzle->label->resize(puzzleSize,puzzleSize);
        newPuzzle->label->setFont(QFont("Snap ITC", newPuzzle->width() / 8));
        (*puzzles)[unsigned(i)] = newPuzzle;
    }

    //ustawianie tła puzzli
    QPixmap puzzleBackground(":/PuzzleBackground/gg_pw.jpg");
    int rectWidth = puzzleBackground.width()/size;
    int rectHeight = puzzleBackground.height()/size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((*puzzles)[unsigned(i*size + j)] != nullptr) {
                QRect rect(rectWidth * i, rectHeight * j, puzzleSize - 10, puzzleSize - 10);
                QPixmap croppedBackground = puzzleBackground.copy(rect);
                QIcon buttonBackground(croppedBackground);
                (*puzzles)[unsigned(j*size + i)]->setIcon(croppedBackground);
                (*puzzles)[unsigned(j*size + i)]->setIconSize(croppedBackground.rect().size());
            }
        }
    }

    //generowanie pozycji puzzli
    std::vector<QPoint> positions(unsigned(pow(size,2)));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            positions[unsigned(i*size + j)] = QPoint(20 + i*puzzleSize, 40 + j*puzzleSize);
        }
    }

    //mieszanie pozycji puzzli
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions.begin(), positions.end(), g);

    //ustawienie pozycji puzzli
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != (size - 1) || j != (size - 1)) {
                (*puzzles)[unsigned(i*size + j)]->move(positions[unsigned(i*size + j)]);
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

Puzzle* GameBoard::getPuzzle(int pos)
{
    return (*puzzles)[unsigned(pos)];
}

Puzzle *GameBoard::getPuzzleByPos(const QPoint &pos)
{
    for (Puzzle *puzzle : *puzzles) {
        if (puzzle != nullptr) {
            if (puzzle->x() == pos.x() && puzzle->y() == pos.y()) {
                return puzzle;
            }
        }
    }
    return nullptr;
}

void GameBoard::setPuzzlePos(int num, const QPoint &pos)
{
    (*puzzles)[unsigned(num)]->move(pos);
}

int GameBoard::getSize()
{
    return int(puzzles->size());
}

void GameBoard::display()
{
    for (int i = 0; i < int(puzzles->size()); i++) {
        if ((*puzzles)[unsigned(i)] != nullptr) {
            (*puzzles)[unsigned(i)]->show();
        }
    }
}

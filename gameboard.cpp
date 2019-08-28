#include <algorithm>
#include <random>
#include <omp.h>
#include "gameboard.h"
#include "puzzle.h"

GameBoard::GameBoard(int level, QWidget *parent)
{
    //inicjalizacja puzzli
    puzzles = new vector<Puzzle*>(unsigned(pow(level,2)));
    int puzzleSize = (parent->size().height() - 140)/level;
    for (int i = 0; i < pow(level,2) - 1; i++) {
        Puzzle* newPuzzle = new Puzzle(QString::fromStdString(to_string(i + 1)), parent);
        newPuzzle->resize(puzzleSize,puzzleSize);
        newPuzzle->getLabel()->resize(puzzleSize,puzzleSize);
        newPuzzle->getLabel()->setFont(QFont("Snap ITC", newPuzzle->height() / 8));
        (*puzzles)[unsigned(i)] = newPuzzle;
    }

    //ustawianie tła puzzli
    QPixmap puzzleBackground(":/PuzzleBackground/gg_pw.jpg");
    int rectWidth = puzzleBackground.width()/level;
    int rectHeight = puzzleBackground.height()/level;
    for (int i = 0; i < level; i++) {
        for (int j = 0; j < level; j++) {
            if ((*puzzles)[unsigned(i*level + j)] != nullptr) {
                QRect rect(rectWidth * i, rectHeight * j, puzzleSize - 10, puzzleSize - 10);
                QPixmap croppedBackground = puzzleBackground.copy(rect);
                QIcon buttonBackground(croppedBackground);
                (*puzzles)[unsigned(j*level + i)]->setIcon(croppedBackground);
                (*puzzles)[unsigned(j*level + i)]->setIconSize(croppedBackground.rect().size());
            }
        }
    }

    //generowanie pozycji puzzli
    vector<QPoint> basePositions(unsigned(pow(level,2)));
    for (int i = 0; i < level; i++) {
        for (int j = 0; j < level; j++) {
            basePositions[unsigned(j*level + i)] = QPoint(20 + i*puzzleSize, 40 + j*puzzleSize);
        }
    }

    //mieszanie pozycji puzzli
    vector<QPoint> positions(basePositions);
    QPoint emptyPos(positions.back());
    QPoint lastEmptyPos = emptyPos;
    vector<QPoint> emptyNeighbors;
    sollution = new vector<int>;
    for (int i = 0; i < pow(level, level); i++) {
        for (QPoint position : positions) {
            //jeżeli nie jest poprzednio ruszanym puzzlem i jest puzzlem sąsiadującym z pustym puzzlem
            if ((position.x() != lastEmptyPos.x() || position.y() != lastEmptyPos.y()) &&
                ((position.x() == emptyPos.x() && position.y() == emptyPos.y() + puzzleSize) ||
                 (position.x() == emptyPos.x() && position.y() == emptyPos.y() - puzzleSize) ||
                 (position.x() == emptyPos.x() + puzzleSize && position.y() == emptyPos.y()) ||
                 (position.x() == emptyPos.x() - puzzleSize && position.y() == emptyPos.y()))) {
                if (position.x() == emptyPos.x() || position.y() == emptyPos.y()) {
                    emptyNeighbors.push_back(position);
                }
            }
        }

        lastEmptyPos = emptyPos;

        random_device rd;
        mt19937 g(rd());
        shuffle(emptyNeighbors.begin(), emptyNeighbors.end(), g);

        vector<QPoint>::iterator emptyPosIter = find(positions.begin(), positions.end(),emptyPos);
        vector<QPoint>::iterator movePosIter = find(positions.begin(), positions.end(), emptyNeighbors[0]);

        //znalezienie pozycji przesuwanego puzzla względem bazowych pozycji i dodanie puzzla do rozwiązania
        vector<QPoint>::iterator moveIter = find(positions.begin(), positions.end(), *movePosIter);
        int moveIndex = int(distance(positions.begin(), moveIter));
        sollution->push_back(moveIndex + 1);

        //zamiana przyszłych pozycji puzzli
        swap(*emptyPosIter, *movePosIter);

        //aktualizacja pozycji pustego puzzla
        emptyPos = *emptyPosIter;

        emptyNeighbors.clear();
    }

    //znajdowanie rozmieszczenia puzzli
    placement = new vector<int>;
    for(QPoint position : basePositions){
        vector<QPoint>::iterator it = find(positions.begin(), positions.end(), position);
        int index = int(distance(positions.begin(), it));
        placement->push_back((index + 1) % int(puzzles->size())); //żeby 0 zamiast ostatniego
    }

    //ustawienie pozycji puzzli
    for (int i = 0; i < level; i++) {
        for (int j = 0; j < level; j++) {
            if (i != (level - 1) || j != (level - 1)) {
                (*puzzles)[unsigned(i*level + j)]->move(positions[unsigned(i*level + j)]);
            }
        }
    }
}

GameBoard::GameBoard(const GameBoard &gameBoard, QWidget *parent)
{
    sollution = new vector<int>;
    for (int step : *(gameBoard.sollution)) {
        sollution->push_back(step);
    }

    placement = new vector<int>;
    for (int value : *(gameBoard.placement)) {
        placement->push_back(value);
    }

    puzzles = new vector<Puzzle*>(gameBoard.puzzles->size());
    int puzzleSize = (*gameBoard.puzzles->begin())->height();
    for (int i = 0; i < int(gameBoard.puzzles->size()) - 1; i++) {
        Puzzle* newPuzzle = new Puzzle(QString::fromStdString(to_string(i + 1)), parent);
        newPuzzle->resize(puzzleSize, puzzleSize);
        newPuzzle->getLabel()->resize(puzzleSize, puzzleSize);
        newPuzzle->getLabel()->setFont(QFont("Snap ITC", newPuzzle->height() / 8));

        Puzzle* pattern = (*gameBoard.puzzles)[unsigned(i)];
        int level = int(sqrt(gameBoard.puzzles->size()));
        newPuzzle->setIcon(pattern->icon());
        newPuzzle->setIconSize(pattern->iconSize());
        newPuzzle->move(pattern->pos().x() + pattern->width()*level + 20, pattern->pos().y());

        //vector<int>::iterator placeIter = find(placement->begin(), placement->end(), i + 1);
        //int placeIndex = int(distance(placement->begin(), placeIter));
        (*puzzles)[unsigned(i)] = newPuzzle;
    }
}

GameBoard::~GameBoard()
{
    if (puzzles != nullptr) {
        for (Puzzle *puzzle : *puzzles) {
            delete puzzle;
        }
        puzzles->clear();
    }
}

vector<Puzzle *> *GameBoard::getPuzzles()
{
    return puzzles;
}

Puzzle* GameBoard::getPuzzle(int pos)
{
    return (*puzzles)[unsigned(pos)];
}

Puzzle* GameBoard::getPuzzleByPos(const QPoint &pos)
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

    int moveIndex = -1;
    int emptyIndex = -1;
    for (int i = 0; i < int(placement->size()); i++) {
        if((*placement)[unsigned(i)] == num + 1) {
            moveIndex = i;
        }
        if((*placement)[unsigned(i)] == 0) {
            emptyIndex = i;
        }
    }

    (*placement)[unsigned(moveIndex)] = 0;
    (*placement)[unsigned(emptyIndex)] = num + 1;
}

vector<int>* GameBoard::getSollution()
{
    return sollution;
}

vector<int>* GameBoard::getPlacement()
{
    return placement;
}

bool GameBoard::isSolved(void)
{
    for (int i = 0; i < int(placement->size()) - 1; i++) {
        if ((*placement)[unsigned(i)] != (i + 1)) {
            return false;
        }
    }

    return true;
}

void GameBoard::display()
{
    for (int i = 0; i < int(puzzles->size()); i++) {
        if ((*puzzles)[unsigned(i)] != nullptr) {
            (*puzzles)[unsigned(i)]->show();
        }
    }
}

#include "humanplayer.h"

HumanPlayer::HumanPlayer(string name)
{
    this->name = name;
}

HumanPlayer::~HumanPlayer()
{
    ;
}

void HumanPlayer::movePuzzle(GameBoard *gameBoard, QToolButton *clickedButton)
{
    QPoint puzzlePos = clickedButton->pos();
    int puzzleNum = clickedButton->text().toInt();
    int puzzleSize = clickedButton->width();
    int level = int(sqrt(gameBoard->getPuzzles()->size()));

    /*! jeżeli górny wolny */
    if (puzzlePos.y() >= 40 + puzzleSize) {
        if (gameBoard->getPuzzleByPos(QPoint(puzzlePos.x(), puzzlePos.y() - puzzleSize)) == nullptr) {
            gameBoard->setPuzzlePos(puzzleNum - 1, QPoint(puzzlePos.x(), puzzlePos.y() - puzzleSize));
            return;
        }
    }

    /*! jeżeli dolny wolny */
    if (puzzlePos.y() < 40 + puzzleSize*(level - 1)) {
        if (gameBoard->getPuzzleByPos(QPoint(puzzlePos.x(), puzzlePos.y() + puzzleSize)) == nullptr) {
            gameBoard->setPuzzlePos(puzzleNum - 1, QPoint(puzzlePos.x(), puzzlePos.y() + puzzleSize));
            return;
        }
    }

    /*! jeżeli lewy wolny */
    if (puzzlePos.x() >= 20 + puzzleSize) {
        if (gameBoard->getPuzzleByPos(QPoint(puzzlePos.x() - puzzleSize, puzzlePos.y())) == nullptr) {
            gameBoard->setPuzzlePos(puzzleNum - 1, QPoint(puzzlePos.x() - puzzleSize, puzzlePos.y()));
            return;
        }
    }

    /*! jeżeli prawy wolny */
    if (puzzlePos.x() < 20 + puzzleSize*(level - 1)) {
        if (gameBoard->getPuzzleByPos(QPoint(puzzlePos.x() + puzzleSize, puzzlePos.y())) == nullptr) {
            gameBoard->setPuzzlePos(puzzleNum - 1, QPoint(puzzlePos.x() + puzzleSize, puzzlePos.y()));
            return;
        }
    }
}

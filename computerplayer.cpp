#include "computerplayer.h"

ComputerPlayer::ComputerPlayer()
{
    name = "Komputer";
}

ComputerPlayer::~ComputerPlayer()
{
    ;
}

void ComputerPlayer::movePuzzle(GameBoard* gameBoard, QToolButton *)
{
    int puzzleNum = gameBoard->getSollution()->back();
    QPoint puzzlePos = gameBoard->getPuzzle(puzzleNum - 1)->pos();
    int puzzleSize = gameBoard->getPuzzle(puzzleNum - 1)->height();
    int level = int(sqrt(gameBoard->getPuzzles()->size()));
    gameBoard->getSollution()->pop_back();

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
    if (puzzlePos.x() >= 20 + puzzleSize*(1 + level)) {
        if (gameBoard->getPuzzleByPos(QPoint(puzzlePos.x() - puzzleSize, puzzlePos.y())) == nullptr) {
            gameBoard->setPuzzlePos(puzzleNum - 1, QPoint(puzzlePos.x() - puzzleSize, puzzlePos.y()));
            return;
        }
    }

    /*! jeżeli prawy wolny */
    if (puzzlePos.x() < 20 + puzzleSize*(2*level - 1)) {
        if (gameBoard->getPuzzleByPos(QPoint(puzzlePos.x() + puzzleSize, puzzlePos.y())) == nullptr) {
            gameBoard->setPuzzlePos(puzzleNum - 1, QPoint(puzzlePos.x() + puzzleSize, puzzlePos.y()));
            return;
        }
    }
}

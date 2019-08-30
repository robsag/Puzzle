#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <player.h>

/// Klasa reprezentuje gracza, którym jest komputer
class ComputerPlayer : public Player
{
public:
    /// Konstruktor domyślny
    ComputerPlayer();

    /// Destruktor wirtualny
    ~ComputerPlayer();

    /**
    * Metoda przesuwa puzzle, które układa gracz komputer (program)
    *
    * \param[in] GameBoard* wskaźnik do planszy zawierającej puzzle
    * \param[in] QToolButton* kliknięty przycisk
    */
    void movePuzzle(GameBoard*, QToolButton*);
};

#endif // COMPUTERPLAYER_H

#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <player.h>

/// Klasa reprezentuje gracza, którym jest użytkownik
class HumanPlayer : public Player
{
public:
    /**
    * Konstruktor z parametrem
    *
    * \param[in] string imię gracza człowieka (użytkownika)
    */
    HumanPlayer(string);

    /// Destruktor wirtualny
    ~HumanPlayer();

    /**
    * Metoda przesuwa puzzle, które układa gracz komputer (program)
    *
    * \param[in] GameBoard* wskaźnik do planszy zawierającej puzzle
    * \param[in] QToolButton* kliknięty przycisk
    */
    void movePuzzle(GameBoard*, QToolButton*);
};

#endif // HUMANPLAYER_H

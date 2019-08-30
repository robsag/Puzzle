#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <gameboard.h>

using namespace std;

/// Klasa reprezentuje gracza
class Player
{
public:
    /// Konstruktor domyślny
    Player();

    /// Destruktor wirtualny
    virtual ~Player();

    /**
    * Metoda zwracająca imię gracza
    *
    * \return name imię gracza
    */
    string getName(void);

    /**
    * Metoda czysto wirtualna, przesuwa puzzle, które układa gracz
    *
    * \param[in] GameBoard* wskaźnik do planszy zawierającej puzzle
    * \param[in] QToolButton* kliknięty przycisk
    */
    virtual void movePuzzle(GameBoard*, QToolButton* = nullptr) = 0;

protected:
    string name; /*!< imię gracza */
};

#endif // PLAYER_H

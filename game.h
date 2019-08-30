#ifndef GAME_H
#define GAME_H

#include <string>
#include <gameboard.h>
#include <player.h>
#include <mainwindow.h>

using namespace std;

/// Klasa reprezentuje grę puzzle
class Game : public QObject
{
public:
    /**
    * Konstruktor z parametrami
    *
    * \param[in] QWidget* rodzic tworzonej instancji klasy
    * \param[in] QString imię gracza
    * \param[in] int rozmiar puzzli, liczba puzzli wzdłóż jednego boku planszy
    * \param[in] bool informacja o trybie gry, jednoosobowy lub z komputerem, domyślnie ustawiony na jednoosobowy (true)
    */
    Game(QWidget*, QString, int, bool = true);

    /**
    * Konstruktor z parametrami
    *
    * \param[in] const QString& tekst etykiety puzzla
    * \param[in] QWidget* rodzic tworzonej instancji klasy
    */
    Game(QWidget *parent, string);

    /// Destruktor
    ~Game();

    /**
    * Metoda zwracająca wskaźnik do planszy gry
    *
    * \param[in] int numer planszy gry (użytkownika lub komputera), domyślnie ustawiony na planszę użytkownika (1)
    * \return GameBoard* wskaźnik do planszy gry
    */
    GameBoard* getGameBoard(int = 1);

    /**
    * Metoda zwracająca wskaźnik do gracza
    *
    * \param[in] int numer gracza (użytkownik lub komputer), domyślnie ustawiony na gracza użytkownika (1)
    * \return *Player wskaźnik do gracza
    */
    Player* getPlayer(int = 1);

    /**
    * Metoda zwracająca czas gry w milisekundach
    *
    * \return int czas gry
    */
    int getTime(void);

    /**
    * Metoda ustawiająca czas gry, zapisywany w milisekundach
    *
    * \param[in] int czas gry
    */
    void setTime(int);

    /// Metoda wyświetla puzzle (po wcześniejszym utworzeniu gry)
    void play(void);

    /// Metoda zapisuje grę do pliku tekstowego
    void save(void);

    /// Metoda blokuje puzzle, ustawia właściwości puzzli na brak możliwości kliknięcia
    void disable(void);

private:
    GameBoard *gameBoard1; /*!< wskaźnik do planszy gry użytkownika */
    GameBoard *gameBoard2; /*!< wskaźnik do planszy gry komputera */
    Player *player1; /*!< wskaźnik do gracza, użytkownika */
    Player *player2; /*!< wskaźnik do gracza, komputera */
    int time; /*!< czas gry */
};

#endif // GAME_H

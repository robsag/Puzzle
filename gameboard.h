#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <puzzle.h>

using namespace std;

/// Klasa reprezentuje planszę, na której układane są puzzle
class GameBoard
{
public:
    /**
    * Konstruktor z parametrami
    *
    * \param[in] int rozmiar puzzli, liczba puzzli wzdłóż jednego boku planszy
    * \param[in] QWidget* rodzic tworzonej instancji klasy
    */
    GameBoard(int, QWidget*);

    /**
    * Konstruktor z parametrami
    *
    * \param[in] int rozmiar puzzli, liczba puzzli wzdłóż jednego boku planszy gry
    * \param[in] QWidget* rodzic tworzonej instancji klasy
    * \param[in] vector<int> kontener z rozmieszczeniem puzzli
    * \param[in] bool informacja o trybie gry, jednoosobowy lub z komputerem, domyślnie ustawiony na jednoosobowy (true)
    */
    GameBoard(int, QWidget*, vector<int>, bool = true);

    /**
    * Konstruktor kopiujący z dodatkowym parametrem
    *
    * \param[in] const QString& plansza gry
    * \param[in] QWidget* rodzic tworzonej instancji klasy
    */
    GameBoard(const GameBoard&, QWidget*);

    /// Destruktor
    ~GameBoard();

    /**
    * Metoda zwracająca wskaźnik do kontenera z puzzlami
    *
    * \return *puzzles wskaźnik do kontenera z puzzlami
    */
    vector<Puzzle*>* getPuzzles();

    /**
    * Metoda zwracająca wskaźnik do wybranego puzzla
    *
    * \param[in] int indeks puzzla
    * \return (*puzzles)[int] wskaźnik do puzzla
    */
    Puzzle* getPuzzle(int);

    /**
    * Metoda zwracająca wskaźnik do wybranego puzzla
    *
    * \param[in] const QPoint& współrzędne położenia puzzla w oknie programu
    * \return (*puzzles)[int] wskaźnik do puzzla
    */
    Puzzle* getPuzzleByPos(const QPoint&);

    /**
    * Metoda ustawiająca współrzędne położenia puzzla w oknie programu
    *
    * \param[in] int indeks puzzla
    * \param[in] const QPoint& współrzędne położenia puzzla w oknie programu
    */
    void setPuzzlePos(int, const QPoint&);

    /**
    * Metoda zwracająca wskaźnik do kontenera z krokami rozwiązującymi puzzle
    *
    * \return *sollution wskaźnik do kontenera z krokami rozwiązującymi puzzle
    */
    vector<int>* getSollution(void);

    /**
    * Metoda zwracająca wskaźnik do kontenera z rozmieszczeniem puzzli
    *
    * \return *placement wskaźnik do kontenera z rozmieszczeniem puzzli
    */
    vector<int>* getPlacement(void);

    /**
    * Metoda zwracająca informację czy puzzle są ułożone
    *
    * \return true jeżeli puzzle są ułożone, false w przeciwnym przypadku
    */
    bool isSolved(void);

    /// Metoda wyświetlająca puzzle w oknie programu
    void display(void);

private:
    vector<Puzzle*> *puzzles; /*!< kontener z puzzlami */
    vector<int> *sollution; /*!< kontener z krokami rozwiązującymi puzzle */
    vector<int> *placement; /*!< kontener z rozmieszczeniem puzzli */
};

#endif // GAMEBOARD_H

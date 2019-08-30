#ifndef PUZZLE_H
#define PUZZLE_H

#include <QToolButton>
#include <QLabel>

/// Klasa reprezentuje pojedynczy element gry, puzzli
class Puzzle : public QToolButton
{
public:
    /**
    * Konstruktor z parametrami
    *
    * \param[in] const QString& tekst etykiety puzzla
    * \param[in] QWidget* rodzic tworzonej instancji klasy
    */
    Puzzle(const QString&, QWidget*);

    /// Destruktor
    ~Puzzle();

    /**
    * Metoda zwracająca wskaźnik do etykiety puzzla
    *
    * \return *label wskaźnik do etykiety puzzla
    */
    QLabel* getLabel(void);

private:
    QLabel *label; /*!< etykieta przedstawiająca numer puzzla */
};

#endif // PUZZLE_H

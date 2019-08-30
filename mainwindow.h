#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Game;

namespace Ui { class MainWindow; }

/// Klasa reprezentuje okno programu
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
    * Konstruktor z parametrem
    *
    * \param[in] QWidget* rodzic tworzonej instancji klasy, domyślnie ustawiony na nullptr
    */
    explicit MainWindow(QWidget *parent = nullptr);

    /// Destruktor
    ~MainWindow();

private slots:
    void on_actionNowa_Gra_triggered(); /*!< Metoda typu slot tworząca nową grę jednoosobową */
    void on_actionNowa_Gra_z_Komputerem_triggered(); /*!< Metoda typu slot tworząca nową grę dwuosobową (z komputerem) */
    void on_actionWczytaj_Gre_triggered(); /*!< Metoda typu slot wczytująca zapisaną grę z pliku tekstowego */
    void on_update_lcdNumber(); /*!< Metoda typu slot aktualizująca czas gry */
    void on_update_computerGame(); /*!< Metoda typu slot aktualizująca położenie puzzli komputera po jego ruchu */
    void on_click_toolButton(); /*!< Metoda typu slot aktualizująca położenie klikniętego puzzla */

private:
    Ui::MainWindow *ui; /*!< wskaźnik do interfejsu użytkownika (elementów okna programu) */
    QTimer *gameTimer; /*!< wskaźnik do stopera mierzącego czas gry */
    QTimer *computerTimer; /*!< wskaźnik do stopera mierzącego czas do ruchu komputera */
    Game *game; /*!< wskaźnik do gry */
};

#endif // MAINWINDOW_H

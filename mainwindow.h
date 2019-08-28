#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Game;

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNowa_Gra_triggered();
    void on_actionNowa_Gra_z_Komputerem_triggered();
    void on_actionWczytaj_Gre_triggered();
    void on_update_lcdNumber();
    void on_update_computerGame();
    void on_click_toolButton();

private:
    Ui::MainWindow *ui;
    QTimer *gameTimer;
    QTimer *computerTimer;
    Game *game;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <game.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNowa_Gra_triggered();
    void on_actionWczytaj_Gre_triggered();
    void on_update_lcdNumber();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    Game *game;
};

#endif // MAINWINDOW_H

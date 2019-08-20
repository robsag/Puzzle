#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_update_lcdNumber()));
    ui->label->setVisible(false);
    ui->timeLabel->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNowa_Gra_triggered()
{
    if (ui->timeLabel->text() != "0:00.00") {
        delete game;
    }
    game = new Game(this);
    game->play();
    timer->start(10);
    ui->label->setVisible(true);
    ui->timeLabel->setVisible(true);

}

void MainWindow::on_actionWczytaj_Gre_triggered()
{
    /*this->game = new Game("save.txt");
    ui->label->setVisible(true);
    ui->timeLabel->setVisible(true);*/
}

void MainWindow::on_update_lcdNumber()
{
    int time = game->getTime();
    int min = time / 6000;
    int sec = (time / 100) % 60;
    int msec = time % 100;
    ui->timeLabel->setText(QString::fromStdString(std::to_string(min))+ ":" +
                           QString::fromStdString(std::string(2 - std::to_string(sec).length(),'0')) +
                           QString::fromStdString(std::to_string(sec))+ "." +
                           QString::fromStdString(std::string(2 - std::to_string(msec).length(),'0')) +
                           QString::fromStdString(std::to_string(msec)));
    game->setTime(game->getTime()+1);
}

void MainWindow::on_click_toolButton(/*Puzzle* puzzle*/)
{
    QToolButton* toolButton = qobject_cast<QToolButton*>(sender());
    if (toolButton) {
        game->getPlayer()->movePuzzle(toolButton, game->getGameBoard());
        //game->getGameBoard()->display();
        if (ui->label->text() != "test1") ui->label->setText("test1");
        else  ui->label->setText("test2");
    }
}

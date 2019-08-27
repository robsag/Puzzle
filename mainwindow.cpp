#include <QTimer>
#include <QMessageBox>
#include <QDesktopWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gameTimer = new QTimer(this);
    connect(gameTimer, SIGNAL(timeout()), this, SLOT(on_update_lcdNumber()));
    ui->label->setVisible(false);
    ui->timeLabel->setVisible(false);

    computerTimer = new QTimer(this);
    connect(computerTimer, SIGNAL(timeout()), this, SLOT(on_update_computerGame()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNowa_Gra_triggered()
{
    if (ui->lineEdit->text() == "") {
        QMessageBox msgBox;
        msgBox.setText("podaj imię gracza");
        msgBox.exec();
        return;
    }

    ui->label2->setVisible(false);
    ui->lineEdit->setVisible(false);

    if (ui->timeLabel->text() != "0:00.00") {
        delete game;
    }

    setMinimumWidth(700);
    setMaximumWidth(700);
    QRect screenGeometry = QRect(QApplication::desktop()->screenGeometry());
    move((screenGeometry.width() - width()) / 2, y());

    game = new Game(this, ui->lineEdit->text(), ui->spinBox->value());
    game->play();
    gameTimer->start(10);
    ui->label->setVisible(true);
    ui->timeLabel->setVisible(true);
}

void MainWindow::on_actionNowa_Gra_z_Komputerem_triggered()
{
    if (ui->lineEdit->text() == "") {
        QMessageBox msgBox;
        msgBox.setText("podaj imię gracza");
        msgBox.exec();
        return;
    }

    ui->label2->setVisible(false);
    ui->lineEdit->setVisible(false);

    if (ui->timeLabel->text() != "0:00.00") {
        delete game;
    }

    setMinimumWidth(1430);
    setMaximumWidth(1430);
    QRect screenGeometry = QRect(QApplication::desktop()->screenGeometry());
    move((screenGeometry.width() - width()) / 2, y());

    game = new Game(this, ui->lineEdit->text(), ui->spinBox->value(), false);
    game->play();
    gameTimer->start(10);
    computerTimer->start(2000);
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

void MainWindow::on_update_computerGame()
{
    //if placement nie jest empty, jak jest to computerTimer->stop
    game->getPlayer2()->movePuzzle(nullptr, game->getGameBoard1());
}

void MainWindow::on_click_toolButton()
{
    QToolButton* toolButton = qobject_cast<QToolButton*>(sender());
    if (toolButton) {
        game->getPlayer1()->movePuzzle(toolButton, game->getGameBoard1());
    }

    if(game->getGameBoard1()->isSolved()) {
        gameTimer->stop();
        computerTimer->stop();
    }
}

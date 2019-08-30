#include <QTimer>
#include <QMessageBox>
#include <QDesktopWidget>
#include <fstream>
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

    ifstream exist("wyniki.txt");
    if (!exist) {
        ofstream results("wyniki.txt", ofstream::out);
        results << "Rozmiar\t\tCzas\t\tGracz";
        results.close();
    }
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
        gameTimer->stop();
        computerTimer->stop();
        delete game;
    }

    remove("zapis");

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
        gameTimer->stop();
        computerTimer->stop();
        delete game;
    }

    remove("zapis");

    setMinimumWidth(1380);
    setMaximumWidth(1380);
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
    ifstream exist("zapis");
    if (exist) {
        exist.close();

        ui->label2->setVisible(false);
        ui->lineEdit->setVisible(false);

        game = new Game(this, "zapis");
        game->play();
        gameTimer->start(10);
        ui->lineEdit->setText(QString::fromStdString(game->getPlayer()->getName()));
        ui->label->setVisible(true);
        ui->timeLabel->setVisible(true);
        if (game->getGameBoard(2) == nullptr) {
            setMinimumWidth(700);
            setMaximumWidth(700);
        } else {
            computerTimer->start(2000);
            setMinimumWidth(1380);
            setMaximumWidth(1380);
        }
        QRect screenGeometry = QRect(QApplication::desktop()->screenGeometry());
        move((screenGeometry.width() - width()) / 2, y());
    } else {
        QMessageBox msgBox;
        msgBox.setText("brak zapisanej gry");
        msgBox.exec();
    }
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
    game->getPlayer(2)->movePuzzle(game->getGameBoard(2));
    game->save();

    if (game->getGameBoard(2)->isSolved()) {
        gameTimer->stop();
        computerTimer->stop();
        game->disable();

        QMessageBox msgBox;
        msgBox.setText("Komputer wygrywa!");
        msgBox.exec();

        remove("zapis");
    }
}

void MainWindow::on_click_toolButton()
{
    QToolButton* toolButton = qobject_cast<QToolButton*>(sender());
    if (toolButton) {
        game->getPlayer()->movePuzzle(game->getGameBoard(), toolButton);
        game->save();
    }

    if(game->getGameBoard()->isSolved()) {
        gameTimer->stop();
        computerTimer->stop();
        game->disable();

        QMessageBox msgBox;
        msgBox.setText(ui->lineEdit->text() + " wygrywa!");
        msgBox.exec();

        ofstream results("wyniki.txt", ofstream::app);
        results << endl << sqrt(game->getGameBoard()->getPuzzles()->size()) << "\t\t" <<
                   ui->timeLabel->text().toStdString() << "\t\t" <<
                   ui->lineEdit->text().toStdString();
        results.close();

        remove("zapis");
    }
}

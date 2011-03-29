#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QLayout>
#include <QKeyEvent>
#include <QTimer>
#include <QShortcut>
#include <QCheckBox>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenuBar>

#include "mainwindow.h"
#include "Paon.hh"

MainWindow::MainWindow(Paon& game)
    : QMainWindow(0),
      _game(game),
      _graph(new Graphic(game, this)),
      _optionWindow(new OptionWindow(this)),
      _scoreTitle(new QLabel(TEXT_SCORE, this)),
      _lcdScore(new QLCDNumber (this)),
      _timer(new QTimer(this))
{
    // Set Size
    this->setFixedSize(10 * game.getSize().first + 190, 10 * game.getSize().second + 60);

    // Set KeyTab correspondancy
    this->setKeyTab();
    this->_lastKey.first = Paon::KEY_NO;
    this->_lastKey.second = Paon::KEY_NO;

    // Connect
    connect(this->_timer, SIGNAL(timeout()), this, SLOT(sendKey()));

    // Menu && Actions
    this->menuBar()->resize(this->width(), 30);
    this->menuBar()->addAction(TEXT_QUIT, this, SLOT(close()));
    this->menuBar()->addAction(TEXT_START, this, SLOT(startPauseGame()));
    this->menuBar()->addAction(TEXT_NEW, this, SLOT(newGame()));
    this->menuBar()->addAction(TEXT_OPTION, this->_optionWindow, SLOT(show()));

    // Extra Score Widget
    this->_lcdScore->setSegmentStyle(QLCDNumber::Flat);
    this->_lcdScore->setFixedWidth(100);
    this->_scoreTitle->move(this->width() - 160, this->height() - 100);
    this->_lcdScore->move(this->width() - 110, this->height() - 105);

    // Set Focus
    this->_graph->setFocusPolicy(Qt::StrongFocus);
    this->isActiveWindow();
}

MainWindow::~MainWindow()
{
    delete this->_scoreTitle;
    delete this->_lcdScore;
    delete this->_graph;
    delete this->_optionWindow;
    this->menuBar()->clear();
    this->_key.clear();
}

Paon const&  MainWindow::getGame() const
{
    return (this->_game);
}

void            MainWindow::setKeyTab()
{
    this->_key[Qt::Key_Up] = Paon::KEY_UP;
    this->_key[Qt::Key_Down] = Paon::KEY_DOWN;
    this->_key[Qt::Key_Left] = Paon::KEY_LEFT;
    this->_key[Qt::Key_Right] = Paon::KEY_RIGHT;
    this->_key[Qt::Key_W] = Paon::KEY_UP;
    this->_key[Qt::Key_S] = Paon::KEY_DOWN;
    this->_key[Qt::Key_A] = Paon::KEY_LEFT;
    this->_key[Qt::Key_D] = Paon::KEY_RIGHT;
}

void            MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        this->close();
    if (this->_timer->isActive())
    {
        if (WHICH_PLAYER(event->key()))
            this->_lastKey.second = this->_key[event->key()];
        else
            this->_lastKey.first = this->_key[event->key()];
    }
}

void            MainWindow::sendKey()
{
    std::pair<bool, bool>    gameStatus = this->_game.manageKey(this->_lastKey);

    this->_lastKey.first = Paon::KEY_NO;
    this->_lastKey.second = Paon::KEY_NO;
    if (!gameStatus.first || !gameStatus.second)
    {
        if (!gameStatus.first ^ !gameStatus.second)
            QMessageBox::information(this, TEXT_GO, WHICH_PTEXT(gameStatus.first));
        else
            QMessageBox::information(this, TEXT_GO, TEXT_PLBO);
        this->stopGame();
    }
    else
    {
        this->update();
        if (!this->_optionWindow->getMulti() && this->_lcdScore->value() != this->_game.getScore())
        {
            this->_lcdScore->display(this->_game.getScore());
            if (!(this->_game.getScore() % 5) && this->_game.getScore() && this->_time > 10)
                this->_timer->start((this->_time -= 2));
        }
    }
}

void            MainWindow::newGame()
{
    this->_game.newGame(this->_optionWindow->getMulti(), this->_optionWindow->getWallVisibility());
    this->_time = DEFAULT_TIME;
    if (this->_optionWindow->getMulti())
    {
        this->_lcdScore->hide();
        this->_scoreTitle->hide();
    }
    else
    {
        this->_lcdScore->show();
        this->_scoreTitle->show();
    }
    this->update();
}

void            MainWindow::stopGame()
{
    this->_timer->stop();
}

void            MainWindow::startPauseGame()
{
    if (this->_timer->isActive())
        this->_timer->stop();
    else
        this->_timer->start(this->_time);
}

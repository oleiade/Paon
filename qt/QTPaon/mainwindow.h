#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include    <QtGui/QWidget>
#include    <QLabel>
#include    <QLCDNumber>
#include    <QPushButton>
#include    <QVBoxLayout>
#include    <QRadioButton>
#include    <QCheckBox>
#include    <QSpinBox>
#include    <QKeyEvent>

#include    <QMainWindow>

#include    "Paon.hh"
#include    "optionwindow.h"
#include    "graphic.h"

#define     TEXT_FILE       "&File"
#define     TEXT_GAME       "&Game"
#define	    WHICH_PTEXT(x)  (!x) ? TEXT_PLAO : TEXT_PLAT
#define     TEXT_TITLE      "::QtPaon::"
#define     TEXT_SCORE      "Score :"
#define     TEXT_NEW        "&New"
#define     TEXT_QUIT       "&Quit"
#define     TEXT_START      "&Start/Pause"
#define     TEXT_OPTION     "&Options"
#define     DEFAULT_TIME    this->_optionWindow->getMulti() ? 40 : 80
#define     LEVEL_MAX       10
#define     LEVEL_MIN       1
#define     CASE            25
#define     WHICH_PLAYER(x) ((x == Qt::Key_Up || x == Qt::Key_Down || x == Qt::Key_Left || x == Qt::Key_Right) ? (false) : (true))
#define     PAIR_KEYCODE    std::pair<Paon::eKey, Paon::eKey>

class       MainWindow :    public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Paon& game);
    virtual ~MainWindow();

private:
    PAIR_KEYCODE                                _lastKey;
    Paon&                                    _game;

    // Graphic Scene
    Graphic                                     *_graph;

    // Graphic Accesories
    OptionWindow                                *_optionWindow;
    QLabel                                      *_scoreTitle;
    QLCDNumber                                  *_lcdScore;
    QTimer                                      *_timer;
    int                                         _time;
    std::map<int, Paon::eKey>                _key;

private:
    void                                        setKeyTab();

public:
    Paon const&                              getGame()   const;

protected:
    void                                        keyPressEvent(QKeyEvent *event);

private slots:
    void                                        sendKey();
    void                                        newGame();
    void                                        stopGame();
    void                                        startPauseGame();
};

#endif // MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>

#include "mainwindow.h"
#include "optionwindow.h"

OptionWindow::OptionWindow(QWidget *parent) :
    QMainWindow(parent),
    _multiButton(new QCheckBox(TEXT_MULTI, this)),
    _wallButton(new QCheckBox(TEXT_WALL, this)),
    _levelButton(new QSpinBox(this)),
    _okButton(new QPushButton(TEXT_OK, this)),
    _levelTitle(new QLabel(TEXT_LEVEL, this)),
    _multi(false), _level(1), _wallVisibility(true)
{
    this->setWindowTitle(TEXT_OPTION_WIN);
    this->setFixedSize(OPTION_WIN_X, OPTION_WIN_Y);
    this->setParent(parent);
    this->_wallButton->setChecked(true);
    this->_levelButton->setMinimum(LEVEL_MIN);
    this->_levelButton->setMaximum(LEVEL_MAX);
    this->_levelButton->setMaximumWidth(40);
    this->_levelButton->setMaximumHeight(25);

    this->_levelTitle->move(20, 80);
    this->_levelButton->move(120, 80);
    this->_multiButton->move(20, 50);
    this->_wallButton->move(20, 20);
    this->_okButton->move(40, 120);

    connect(this->_okButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(this->_multiButton, SIGNAL(clicked()), this, SLOT(changeMulti()));
    connect(this->_wallButton, SIGNAL(clicked()), this, SLOT(changeWall()));
}

OptionWindow::~OptionWindow()
{
    delete this->_multiButton;
    delete this->_wallButton;
    delete this->_levelButton;
    delete this->_levelTitle;
    delete this->_okButton;
}

void            OptionWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape || event->key() == Qt::Key_Return)
        this->close();
}

bool            OptionWindow::getMulti()                const
{
    return (this->_multi);
}

bool            OptionWindow::getWallVisibility()       const
{
    return (this->_wallVisibility);
}

int             OptionWindow::getLevel()                const
{
    return (this->_level);
}

void            OptionWindow::updateLevel(int level)
{
    this->_level = level;
}

void            OptionWindow::changeWall()
{
    ((this->_wallVisibility == true) ? (this->_wallVisibility = false) : (this->_wallVisibility = true));
}

void            OptionWindow::changeMulti()
{
    ((this->_multi == true) ? (this->_multi = false) : (this->_multi = true));
}

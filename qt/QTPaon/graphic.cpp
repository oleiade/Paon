#include <QPainter>
#include <QKeyEvent>


#include "Paon.hh"
#include "mainwindow.h"
#include "graphic.h"

Graphic::Graphic(Paon& game, QWidget *parent) :
    QWidget(parent),
    _game(game),
    _snakeList(game.getSnakeList()),
    _wallList(game.getWallList()),
    _foodList(game.getFoodList()),
    _plateSize(game.getSize())
{
    this->setColor();
    this->setFixedSize(10 * game.getSize().first, 10 * game.getSize().second);
    this->move(20, 40);
}

Graphic::~Graphic()
{
    this->_color.clear();
}

void            Graphic::drawListElem(std::list<Item> const& list)
{
    QPainter    painter(this);

    if (list.front().getType() == Item::SNAKE)
        painter.setPen(QColor("white"));
    else if (list.front().getType() == Item::WALL)
        painter.setPen(QColor("gray"));
    else
        painter.setPen(QColor("yellow"));
    for (std::list<Item>::const_iterator it = list.begin();
         it != list.end(); ++it)
    {
        painter.setBrush(QColor(this->_color[(*it).getColor()]));
        painter.drawRect(((*it).getCoor().first * this->width()) / this->_plateSize.first,
                         ((*it).getCoor().second * this->height()) / this->_plateSize.second,
                         this->width() / this->_plateSize.first,
                         this->height() / this->_plateSize.second);
    }
}

void            Graphic::paintEvent(QPaintEvent *event)
{
    QPainter    painter(this);

    painter.setPen(QColor("black"));
    painter.setBrush(QBrush("black"));
    painter.drawRect(0, 0, this->width() - 1, this->height() - 1);
    this->drawListElem(this->_snakeList.first);
    this->drawListElem(this->_snakeList.second);
    this->drawListElem(this->_wallList);
    this->drawListElem(this->_foodList);
}

void            Graphic::setColor()
{
    this->_color[Item::BLACK] = "black";
    this->_color[Item::WHITE] = "white";
    this->_color[Item::GREEN] = "green";
    this->_color[Item::RED] = "red";
    this->_color[Item::YELLOW] = "yellow";
    this->_color[Item::BLUE] = "blue";
    this->_color[Item::GRAY] = "gray";
}

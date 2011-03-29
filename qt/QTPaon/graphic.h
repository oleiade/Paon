#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QFrame>
#include <list>

#include "Item.hh"
#include "Nibbler.hh"

class Graphic : public QWidget
{
  public:
    Graphic(Nibbler& game, QWidget *parent = 0);
    ~Graphic();

private:
    Nibbler&                                                   _game;

    std::pair<std::list<Item>, std::list<Item> >    const&     _snakeList;
    std::list<Item>                                 const&     _wallList;
    std::list<Item>                                 const&     _foodList;
    std::pair<int, int>                             const&     _plateSize;

private:
    std::map<Item::eColor, QString>                             _color;

private:
    void                                            setColor();
    void                                            drawListElem(std::list<Item> const&);

  protected:
    void                                            paintEvent(QPaintEvent *event);

};

#endif // GRAPHIC_H

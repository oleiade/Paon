#include			"../include/Paon.hh"
#include			"../include/Item.hh"

Item::Item(std::pair<int, int> coor, eType type, eColor color) : _type(type), _color(color)
{
    this->_coor = coor;
    this->_type = type;
    this->_color = color;
}

Item::Item()
{
}

Item::Item(Item const& other)
{
    this->_type = other.getType();
    this->_color = other.getColor();
    this->_dir = other.getDir();
    this->_coor = other.getCoor();
}

Item&			Item::operator=(Item const &other)
{
    if (this != &other)
    {
        this->_type = other.getType();
        this->_color = other.getColor();
        this->_dir = other.getDir();
        this->_coor = other.getCoor();
    }
    return (*this);
}

Item::~Item()
{

}

//              Getteurs de case

Item::eType const&              Item::getType() const
{
    return (this->_type);
}

Item::eColor const&             Item::getColor() const
{
    return (this->_color);
}

Item::eDir const&               Item::getDir() const
{
    return (this->_dir);
}

std::pair<int, int> const&      Item::getCoor() const
{
    return (this->_coor);
}

//              Setteurs de case

void                    Item::setType(eType const& newType)
{
    this->_type = newType;
}

void                    Item::setColor(eColor const& newColor)
{
    this->_color = newColor;
}

void                    Item::setDir(eDir const& newDir)
{
    this->_dir = newDir;
}

void                    Item::setCoor(std::pair<int,int> const& coor)
{
    this->_coor = coor;
}

//              Fonction qui permet le mode InvisibleWalls

void                    Item::modulateCoor(std::pair<int, int> const& plateSize)
{
    if (this->_coor.first >= 0)
        this->_coor.first %= plateSize.first;
    else
        this->_coor.first = plateSize.first - 1;
    if (this->_coor.second >= 0)
        this->_coor.second %= plateSize.second;
    else
        this->_coor.second = plateSize.second - 1;
}

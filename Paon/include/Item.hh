#ifndef				_ITEM_HH_
# define			_ITEM_HH_

# include			<utility>

class				Item
{
public:
    enum 				eType
    {
        WALL = 0,
        FOOD,
        SNAKE,
        EMPTY
    };

    enum 				eColor
    {
        WHITE = 0,
        BLACK,
        GREEN,
        RED,
        YELLOW,
        BLUE,
        GRAY
    };

    enum				eDir
    {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT
    };

private:
    eType			_type;
    eColor			_color;
    eDir			_dir;
    std::pair<int, int>		_coor;

public:
    Item();
    Item(std::pair<int, int>, eType, eColor);
    Item(Item const& other);
    Item&                         operator=(Item const &);
    ~Item();

public:
    eType const&                  getType() const;
    eColor const&                 getColor() const;
    eDir const&                   getDir() const;
    std::pair<int,int> const&     getCoor() const;
    void                          modulateCoor(std::pair<int, int> const& plateSize);

    void                          setType(eType const& newType);
    void                          setColor(eColor const& newColor);
    void                          setDir(eDir const& newDir);
    void                          setCoor(std::pair<int,int> const& newCoor);
};

#endif

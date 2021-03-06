#ifndef     __PAON_HH__
# define    __PAON_HH__

# include   <list>
# include   <string>
# include   "IGraph.hh"
# include   "Item.hh"

# define    DEF_SNAKE_SIZE  4
# define    HEAD_COLOR      Item::WHITE
# define    TEXT_GO         "GameOver"
# define    TEXT_PLAO       "Player one died..."
# define    TEXT_PLAT       "Player two died..."
# define    TEXT_PLBO       "Player one and two died..."
# define    WRONG_SIZE      "Please enter plateSize between 20x20 and 200x200"
# define    USAGE           "Paon: Usage: ./Paon x_size y_size lib.so"

# define    IS_UPDATE_DIR(dir, keyCode)                                                                     \
    (((dir == Item::LEFT || dir == Item::RIGHT) && (keyCode == KEY_UP || keyCode == KEY_DOWN)) ||           \
    ((dir == Item::UP || dir == Item::DOWN) && (keyCode == KEY_LEFT || keyCode == KEY_RIGHT)))              \
    ? (true) : (false)

# define    FIRST_WALL      std::pair<int, int>(0, 0), std::pair<int, int>(0, this->getSize().second -1)
# define    SECON_WALL      std::pair<int, int>(0, 0), std::pair<int, int>(this->getSize().first -1, 0)
# define    THIRD_WALL      std::pair<int, int>(this->getSize().first - 1, 0), std::pair<int, int>(this->getSize().first -1, this->getSize().second -1)
# define    FOURT_WALL      std::pair<int, int>(0, this->getSize().second - 1), std::pair<int, int>(this->getSize().first, this->getSize().second - 1)
# define    SOLO_SNAKE      std::pair<int, int>(3, 3), std::pair<int, int>(3, 8)
# define    MULTI_FSNAKE    std::pair<int, int>(3, this->_plateSize.second / 2), std::pair<int, int>(8, this->_plateSize.second / 2)
# define    MULTI_SSNAKE    std::pair<int, int>(this->_plateSize.first -4, this->_plateSize.second / 2), std::pair<int, int>(this->_plateSize.first - 9, this->_plateSize.second / 2)
# define    END_STATE(x)    (x == Item::SNAKE || x == Item::WALL) ? true : false
# define    GOO_STATE(x)    (x == Item::EMPTY || x == Item::FOOD) ? true : false
# define    Y_MOVE(x)       (x == Item::UP || x == Item::DOWN) ? true : false
# define    SET_NCOOR(x, d) (d == Item::RIGHT || d == Item::DOWN) ? (*x)++ : (*x)--
# define    PAIR_LIST_ITEM  std::pair<std::list<Item>, std::list<Item> >


class                                       Paon
{
public :
    enum                                    eKey
    {
	KEY_UP = 0,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ESCAPE,
	KEY_NO
    };

private:
    int                                     _score;
    std::pair<int, int>                     _plateSize;
    PAIR_LIST_ITEM                          _snake;
    std::list<Item>                         _food;
    std::list<Item>                         _wall;
    bool                                    _multi;
    bool                                    _wallVisibility;
    std::pair<eKey, eKey>                   _lastKey;
    IGraph                                  *_lib;

public:
    Paon();
    ~Paon();
    std::pair<bool, bool>                   manageKey(std::pair<eKey, eKey> const& keCode);

private:
    bool                                    makeElem(Item::eColor, Item::eType, std::pair<int, int> = std::pair<int, int>(0, 0), bool = false);
    void                                    makeListElem(std::pair<int, int>, std::pair<int, int>, Item::eColor, Item::eType);
    void                                    clearGame();
    void                                    updateCoor(std::pair<Item, Item>& nItem);
    Item::eType                             isBusyItem(Item const&);
    bool                                    manageFood(std::pair<int, int> const&);
    bool                                    loadLib(char *filename);
    std::string                             checkLibName(char *filename);

public:
    int                                     launchGame(int, char**);
    void                                    newGame(bool, bool);
    int                         const&      getScore()                  const;
    std::pair<int, int>         const&      getSize()                   const;
    std::list<Item>             const&      getWallList()               const;
    std::list<Item>             const&      getFoodList()               const;
    std::string                 const       getStrScore()               const;
    PAIR_LIST_ITEM              const&      getSnakeList()              const;
};

#endif

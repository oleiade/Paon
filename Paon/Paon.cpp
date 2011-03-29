#include    <list>
#include    <cstdlib>
#include    <iostream>
#include    <sstream>
#include    <dlfcn.h>

#include    "../include/Paon.hh"
#include    "../include/Item.hh"

Paon::Paon() :
    _score(0),
    _wallVisibility(true),
    _lib(NULL)
{
}

Paon::~Paon()
{
    this->clearGame();
    if (this->_lib)
        delete this->_lib;
}

//
//                              Fonction publique qui cree une nouvelle  la partie.
//

void				Paon::newGame(bool multi, bool wall)
{
    this->clearGame();
    this->_wallVisibility = wall;

    // Met a jours les parametres du jeu grace aux bool passé par la lib
    this->_multi = multi;
    this->_score = 0;

    if (!multi)
        this->makeListElem(SOLO_SNAKE, Item::RED, Item::SNAKE);
    else
    {
        this->makeListElem(MULTI_FSNAKE, Item::RED, Item::SNAKE);
        this->makeListElem(MULTI_SSNAKE, Item::BLUE, Item::SNAKE);
    }
    if (wall)
    {
	this->makeListElem(FIRST_WALL, Item::GRAY, Item::WALL);
	this->makeListElem(SECON_WALL, Item::GRAY, Item::WALL);
	this->makeListElem(THIRD_WALL, Item::GRAY, Item::WALL);
	this->makeListElem(FOURT_WALL, Item::GRAY, Item::WALL);
    }
    if (!multi)
        this->makeElem(Item::YELLOW, Item::FOOD);
}

//
//                              Fonction privee qui reinitialise la partie
//

void				Paon::clearGame()
{
    this->_snake.first.clear();
    this->_snake.second.clear();
    this->_food.clear();
    this->_wall.clear();
}


//                              Fonction a apeller pour changer les coor
//                              (avec la key + player = false pour 1stp,
//                              player = true pour 2nd player. S'occupe de la bouffe,
//                              Renvoi false quand partie terminee.
std::pair<bool, bool>		Paon::manageKey(std::pair<eKey, eKey> const& keyCode)
{
    std::pair<Item, Item>       nItem;

    nItem.first = this->_snake.first.front();
    if (this->_multi)
        nItem.second = this->_snake.second.front();

    if (IS_UPDATE_DIR(nItem.first.getDir(), keyCode.first) && keyCode.first != Paon::KEY_NO)
        nItem.first.setDir((Item::eDir)keyCode.first);
    if (this->_multi && IS_UPDATE_DIR(nItem.second.getDir(), keyCode.second) && keyCode.second != Paon::KEY_NO)
        nItem.second.setDir((Item::eDir)keyCode.second);

    this->updateCoor(nItem);

    std::pair<Item::eType, Item::eType>     nItemState(isBusyItem(nItem.first),
                                                       this->_multi ? isBusyItem(nItem.second) : Item::EMPTY);

    if (this->_multi && nItem.first.getCoor() == nItem.second.getCoor())
        nItemState = std::pair<Item::eType, Item::eType>(Item::SNAKE, Item::SNAKE);
    if (GOO_STATE(nItemState.first))
    {
        if (nItemState.first != Item::FOOD && !this->_multi)
            this->_snake.first.pop_back();
        this->_snake.first.front().setColor(this->_snake.first.back().getColor());
        this->_snake.first.push_front(nItem.first);
    }
    if (this->_multi && GOO_STATE(nItemState.second))
    {
        this->_snake.second.front().setColor(this->_snake.second.back().getColor());
        this->_snake.second.push_front(nItem.second);
    }
    if (nItemState.first == Item::FOOD && !this->_multi)
        this->manageFood(nItem.first.getCoor());
    return (std::pair<bool, bool>(GOO_STATE(nItemState.first), this->_multi ? GOO_STATE(nItemState.second) : true));
}

//                              Fonction privee qui enleve le food correspondant de la
//                              foodlist et ++ score.
//

bool                            Paon::manageFood(std::pair<int, int> const& coor)
{
    for (std::list<Item>::iterator it = this->_food.begin();
	 it != this->getFoodList().end(); ++it)
	if ((*it).getCoor() == coor)
	{
	    this->_food.erase(it);
	    break ;
	}
    this->_score++;
    return (makeElem(Item::YELLOW, Item::FOOD));
}

//                              Fonction privee qui regarde si la case est occupee
//                              et renvoi le type de l'element.
//

Item::eType			Paon::isBusyItem(Item const& elem)
{
    std::list<Item>             *curList = &this->_snake.first;

    for (std::list<Item>::iterator it = curList->begin(); it != this->_wall.end();)
    {
        for(it = curList->begin(); it != curList->end(); ++it)
            if (elem.getCoor() == (*it).getCoor())
                return ((*it).getType());
        if (curList == &this->_snake.first)
            curList = &this->_snake.second;
        else if (curList == &this->_snake.second)
            curList = &this->_food;
        else if (curList == &this->_food)
            curList = &this->_wall;
    }
    return (Item::EMPTY);
}

//
//                              Fonction privee qui met a jour les coordonee de la
//                              tete des snakes en fonction de leur direction.
//
void                            Paon::updateCoor(std::pair<Item, Item>& nItem)
{
    std::pair<int, int>         newCoor;
    Item                        *curItem = &nItem.first;
    char                        loop = 0;
    int                         *curNewCoor;

    do {
        newCoor = curItem->getCoor();
        curNewCoor = ((Y_MOVE(curItem->getDir())) ? (&newCoor.second) : (&newCoor.first));
        SET_NCOOR(curNewCoor, curItem->getDir());
        curItem->setCoor(newCoor);
        if (!this->_wallVisibility)
            curItem->modulateCoor(this->_plateSize);
        curItem = &nItem.second;
        loop++;
    } while (this->_multi && loop < 2);
}

//
//                              Fonction privee qui cree une liste d'element (snake ou wall).
//

void                            Paon::makeListElem(std::pair<int,int> startPos,
						      std::pair<int,int> endPos,
						      Item::eColor color, Item::eType type)
{
    bool                        nb = (this->_snake.first.size()) ? true : false;
    int&                        curPos = (startPos.first != endPos.first) ? (startPos.first) : (startPos.second);

    do {
	this->makeElem(color, type, startPos, nb);
        if (startPos < endPos)
            curPos++;
        else
            curPos--;
    } while (startPos != endPos);

    if (type == Item::SNAKE)
    {
	Item&                       snakeHead = (!nb) ? (this->_snake.first.front()) : (this->_snake.second.front());
        Item::eDir                  curDir = nb ? Item::LEFT : Item::RIGHT;

        if (!this->_multi)
            curDir = Item::DOWN;
	snakeHead.setColor(Item::WHITE);
        snakeHead.setDir(curDir);
    }
}

//
//                              Fonction privee qui cree un element (unitee de wall/snake) ou food
//

bool                            Paon::makeElem(Item::eColor color, Item::eType type, std::pair<int,int> pos, bool nb)
{
    Item                        elem(pos, type, color);
    std::list<Item>&            curList = ((!nb) ? (this->_snake.first) : (this->_snake.second));
    int                         safety = 0;

    if (type == Item::WALL)
	this->_wall.push_front(elem);
    else if (type == Item::SNAKE)
	curList.push_front(elem);
    else
    {
	do {
	    elem.setCoor(std::pair<int, int>((random() % (this->getSize().first - 2)) + 1,
					     (random() % (this->getSize().second - 2)) + 1));
	    if (safety++ == 100)
		return false;
        } while (this->isBusyItem(elem) != Item::EMPTY);
	this->_food.push_front(elem);
    }
    return true;
}

//
//                              Get le score du serpent sous la forme d'ints.
//

int                 const&      Paon::getScore()         const
{
    return (this->_score);
}

//
//                              Get une ref sur la liste de food
//

std::list<Item>     const&       Paon::getFoodList()      const
{
    return (this->_food);
}

//
//                              Get une ref sur la liste de wall
//

std::list<Item>     const&	Paon::getWallList()      const
{
    return (this->_wall);
}

//
//                              Get une ref sur la taille du plateau
//

std::pair<int, int> const&	Paon::getSize()          const
{
    return (this->_plateSize);
}

//
//                              Get une ref sur la pair de liste de snake
//

PAIR_LIST_ITEM      const&     Paon::getSnakeList()      const
{
    return (this->_snake);
}

//
//                              Get le score sour la forme de string
//

std::string const               Paon::getStrScore()      const
{
    std::ostringstream          oss;

    oss << this->_score;
    return (oss.str());
}

//
//                              Gere le nom de lib
//

std::string                     Paon::checkLibName(char *filename)
{
    std::string                 libNameString = filename;

    if (libNameString.compare(0, 2, "./") != 0)
        libNameString.insert(0, "./");
    return (libNameString);
}

//
//                              Gere l'ouverture de la lib
//

bool                            Paon::loadLib(char *filename)
{
    void                        *dlhandle;
    std::string                 libName = this->checkLibName(filename);

    dlhandle = dlopen(libName.c_str(), RTLD_NOW);
    if (!dlhandle)
    {
        std::cout << dlerror() << std::endl;
        return (false);
    }
    IGraph *(*ptr)() = reinterpret_cast<IGraph* (*)()>(dlsym(dlhandle, "getInstance"));
    if (ptr == NULL)
    {
        std::cout << "Paon: Failed to load symbol from lib." << std::endl;
        return (false);
    }
    this->_lib = ptr();
    return (true);
}

//
//                          Charge la librairie et lance le jeux.
//

int                         Paon::launchGame(int argc, char **argv)
{    
    if (argc != 4)
    {
        std::cout << USAGE << std::endl;
        return (EXIT_FAILURE);
    }
    this->_plateSize.first = atoi(argv[1]);
    this->_plateSize.second = atoi(argv[2]);
    if (this->_plateSize.first < 20 || this->_plateSize.first > 200 ||
            this->_plateSize.second < 20 || this->_plateSize.second > 200)
    {
        std::cerr << WRONG_SIZE << std::endl;
        return (EXIT_FAILURE);
    }
    if (!this->loadLib(argv[3]))
        return (EXIT_FAILURE);
    this->_lib->run(argc, argv, *this);
    return (EXIT_SUCCESS);
}

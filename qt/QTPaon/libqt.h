#ifndef LIBQT_H
#define LIBQT_H

#include "IGraph.hh"
#include "Nibbler.hh"

class LibQt : public IGraph
{
public:
    LibQt() { };
    ~LibQt() { };
    void        run(int ac, char **av, Nibbler& game);
};

extern "C" IGraph*     getInstance();

#endif // LIBQT_H

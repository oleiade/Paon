#include		<iostream>
#include		<dlfcn.h>
#include		<cstdlib>

#include		"../include/Paon.hh"
#include		"../include/IGraph.hh"

int			main(int argc, char **argv)
{
    Paon		game;

    game.launchGame(argc, argv);
    return (EXIT_SUCCESS);
}

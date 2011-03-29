#ifndef			_IGRAPH_HH_
# define		_IGRAPH_HH_

# include		"Paon.hh"

class                   Paon;

class			IGraph
{

  public:
    virtual ~IGraph() {}
    virtual void	run(int, char **, Paon &) = 0;
};

#endif

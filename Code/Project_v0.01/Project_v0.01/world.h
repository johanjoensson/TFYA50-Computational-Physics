#include "atom.h"
#include "verlet_list.h"

class world{
public:
	world();
	world(unsigned int n);
	world(unsigned int x, unsigned int y, unsigned int z, float a);

	unsigned int N;
	atom *atoms;
	verlet_list *bulk;

	void update_verlet_lists();
};
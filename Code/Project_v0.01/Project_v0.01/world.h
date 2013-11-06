#include "atom.h"
#include "verlet_list.h"

class world{
public:
	world();
	world(unsigned int n);

	unsigned int N;
	atom *atoms;
	verlet_list *bulk;

	void update_verlet_lists();
};
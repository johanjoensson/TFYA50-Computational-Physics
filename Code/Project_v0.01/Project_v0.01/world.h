#include "atom.h"
#include "verlet_list.h"
#include "velocity_verlet_integration.h"

class world{
public:
	world();
	world(unsigned int n);

	integrator verlet_integrator;
	unsigned int N;
	atom *atoms;
	verlet_list *bulk;

	void update_verlet_lists();
};
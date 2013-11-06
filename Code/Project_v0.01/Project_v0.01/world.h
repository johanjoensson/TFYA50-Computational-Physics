#include "atom.h"
#include "verlet_list.h"
#include "velocity_verlet_integration.h"

class world{
private:
	float cutoff;
public:
	world();
	world(unsigned int n);
	world(unsigned int x, unsigned int y, unsigned int z, float a);

	integrator verlet_integrator;
	unsigned int N;
	atom *atoms;
	verlet_list *bulk;

	void update_verlet_lists();
};
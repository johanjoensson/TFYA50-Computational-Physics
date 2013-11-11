#include "atom.h"
#include "verlet_list.h"
#include "velocity_verlet_integration.h"

typedef enum {
	KINETIC_ENERGY,
	POTENTIAL_ENERGY,
	TEMPERATURE,
	MSD
}type_of_average;

class world{
private:
	float cutoff;
public:
	world();
	world(unsigned int n);
	world(unsigned int x, unsigned int y, unsigned int z, float a);

	void set_cutoff(float r);

	integrator verlet_integrator;
	unsigned int N;
	atom *atoms;
	verlet_list *bulk;
	float x_tot;        // Total length of the crystal for the respective axes
	float y_tot;
	float z_tot;

	void update_verlet_lists();
	void world_2(unsigned int x, unsigned int y, unsigned int z, float a);
};

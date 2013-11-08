#ifndef VELOCITY_VERLET_INTEGRATION_H
#define VELOCITY_VERLET_INTEGRATION_H

#include "atom.h"
#include "verlet_list.h"
#include "vector_lib.h"

class integrator
{
private:
	float h;
	float cutoff;
	vector_3d calculate_force(atom *atom_a, atom *atom_b);
public:
	integrator();
	void set_cutoff(float r);

	void verlet_integration_position(verlet_list particle);
	void verlet_integration_velocity(verlet_list particle);
};

#endif /* VELOCITY_VERLET_INTEGRATION_H */
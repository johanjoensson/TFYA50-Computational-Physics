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
	vector_3d calculate_force(atom *atom_a, atom *atom_b, float cutoff);
	float x_dim;
	float y_dim;
	float z_dim;

	float e_pot;
	float p_int;
public:
	integrator();
	void set_cutoff(float r);
	void set_dimensions(float x, float y, float z);

	void verlet_integration_position(verlet_list particle);
	void verlet_integration_velocity(verlet_list particle);
	float get_p_int();
	void reset_p_int();
};

#endif /* VELOCITY_VERLET_INTEGRATION_H */

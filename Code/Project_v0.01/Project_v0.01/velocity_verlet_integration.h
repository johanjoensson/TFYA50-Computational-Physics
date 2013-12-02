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
	float sig6;
	float epsi;
	vector_3d calculate_force(atom *atom_a, atom *atom_b);
	float x_dim;
	float y_dim;
	float z_dim;


	float p_int;
	float e_pot;
	PBC boundary;
public:
	integrator();

	void set_timestep(float d);
	void set_cutoff(float r);
	void set_sigma6(float sigma);
	void set_epsilon(float epsilon);
	void set_dimensions(float x, float y, float z);
	void set_PBC(PBC conditions);

	void verlet_integration_position(verlet_list particle);
	void verlet_integration_velocity(verlet_list particle);
	float get_p_int();
	void reset_p_int();

	float get_epot();
	void reset_epot();
};

#endif /* VELOCITY_VERLET_INTEGRATION_H */

#include "velocity_verlet_integration.h"

#include <iostream>

integrator::integrator()
{
	h = 0.2;
}

void integrator::set_cutoff(float r)
{
	cutoff = r;
}

/* TODO - insert the Lenard Jones potential and force calculations */
vector_3d integrator::calculate_force(atom *a, atom *b)
{
	/* THIS IS WRONG, PLEASE CHANGE IT!!! */
	vector_3d res = a->pos - b->pos;
	return res;
}

/* Step 1 of the two step Velocity verlet algorithm. Updates only the position */
void integrator::verlet_integration_position(verlet_list particle)
{
	/* Update position of particle */
	particle.data->pos += particle.data->vel*h + 0.5*particle.data->acc*h*h;

	/* Store the acceleration of the particle for use in step 2 */
	particle.data->acc = particle.data->next_acc;
	particle.data->next_acc = vector_3d(0, 0, 0);
}

float distance_atoms(vector_3d a, vector_3d b)
{
	return (a-b).abs();
}

/* The second part of the Velocity verlet algorithm, updates velocity */
void integrator::verlet_integration_velocity(verlet_list particle)
{
	verlet_list *current = particle.next;
	vector_3d tmp_force;

	while(current != 0){
		if(distance_atoms(current->data->pos, particle.data->pos) < cutoff){
			/* Update velocity and acceleration of the particle */
			tmp_force = calculate_force(particle.data, current->data);
			/* Add division by mass of particle */
			particle.data->next_acc += tmp_force;
			current->data->next_acc -= tmp_force;
		}
		current = current->next;
	}	
	
	particle.data->vel += 0.5*(particle.data->acc + particle.data->next_acc)*h;
}
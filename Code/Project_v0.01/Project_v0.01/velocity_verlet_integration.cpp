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

/* TODO - insert the Lennard-Jones potential and force calculations */
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
	vector_3d move = particle.data->vel*h + 0.5*particle.data->acc*h*h;
	particle.data->incr_displacement(move.abs());
	particle.data->pos += move;
}

float distance_atoms(vector_3d a, vector_3d b)
{
	return (a-b).abs();
}

/* The second part of the Velocity verlet algorithm, updates velocity */
void integrator::verlet_integration_velocity(verlet_list particle)
{
	verlet_list *current = particle.next;
	vector_3d tmp_force = vector_3d(0,0,0);

	while(current != 0){
		if(distance_atoms(current->data->pos, particle.data->pos) < cutoff){
			/* Update velocity and acceleration of the particle */
			tmp_force = calculate_force(particle.data, current->data);
			/* Add division by mass of particle */
			particle.data->incr_next_acc(tmp_force/particle.data->mass);
			current->data->decr_next_acc(tmp_force/current->data->mass);
		}
		current = current->next;
	}	
	
	particle.data->vel += 0.5*(particle.data->acc + particle.data->get_next_acc())*h;
	particle.data->update_acceleration();

}

vector_3d calculate_force(atom *atom_a, atom *atom_b, float cutoff)
{
	float ff=0;
	vector_3d f = vector_3d();
	vector_3d a = atom_a->pos;
	vector_3d b = atom_b->pos;
	vector_3d d = a-b;
	float r = a.distance(b);
	float ri = 1/r;
	float ri2 = ri*ri;
	float ri6 = ri2*ri2*ri2;
	float ff = 48*(ri*ri6*ri6-0,5*ri*ri6);
	vector_3d f = d*ff*ri;
	float ecut = 4*ri6*(ri6-1);
	float rc3 = cutoff*cutoff*cutoff;
	float en = en +  4*rc3*rc3*(rc3*rc3-1) - ecut;
	float partpint = partpint + d*f;
}


const float kB = 8.6173324e-5;

//Temperature
float T = 0;

for(i=0; i<N; i++){
	T = T + atom_mass * atoms[i].vel * atoms[i].vel;
}
T = T / (3*kB*N);

//internal pressure
float P = N*kB*T/V;
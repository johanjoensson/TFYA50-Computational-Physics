#include "velocity_verlet_integration.h"

#include <iostream>

integrator::integrator()
{
	h = 0.2;
	e_pot = 0;
	//p_int = 0;
}

void integrator::set_cutoff(float r)
{
	cutoff = r;
}

void integrator::set_dimensions(float x, float y, float z)
{
	x_dim = x;
	y_dim = y;
	z_dim = z;
}

/* Step 1 of the two step Velocity verlet algorithm. Updates only the position */
void integrator::verlet_integration_position(verlet_list particle)
{
	/* Update position of particle */
	std::cout << "Updating position" << std::endl;
	vector_3d move = particle.data->vel*h + 0.5*particle.data->acc*h*h;
	particle.data->incr_displacement(move.abs());
	particle.data->pos += move;
}

/* The second part of the Velocity verlet algorithm, updates velocity */
void integrator::verlet_integration_velocity(verlet_list particle)
{
	verlet_list *current = particle.next;
	vector_3d tmp_force = vector_3d(0,0,0);

	while(current != 0){
		vector_3d r = particle.data->pos.diff(current->data->pos, x_dim, y_dim, z_dim);
		if(r*r < cutoff*cutoff){
			/* Update velocity and acceleration of the particle */
			std::cout << "Calculating force\t";
			tmp_force = calculate_force(particle.data, current->data);
			particle.data->incr_next_acc(tmp_force/particle.data->mass);
			current->data->decr_next_acc(tmp_force/current->data->mass);
		}
		current = current->next;
	}	
	
	particle.data->vel += 0.5*(particle.data->acc + particle.data->get_next_acc())*h;
	particle.data->update_acceleration();

}

vector_3d integrator::calculate_force(atom *atom_a, atom *atom_b)
{
	float ff=0;
	vector_3d a = atom_a->pos;
	vector_3d b = atom_b->pos;
	vector_3d d = a.diff(b, x_dim, y_dim, z_dim);
	float r = a.distance(b, x_dim, y_dim, z_dim);
	float ri = 1/r;
	float ri2 = ri*ri;
	float ri6 = ri2*ri2*ri2;
	ff = 48*(ri*ri6*ri6-0,5*ri*ri6);
	vector_3d f = d*ff*ri;
	float ecut = 4*ri6*(ri6-1);
	float rc3 = cutoff*cutoff*cutoff;
	/* accumulate the potential enegry */
	e_pot += 4*rc3*rc3*(rc3*rc3-1) - ecut;
	/* First part of internal pressure */
	p_int += d*f;
//	std::cout << "force: " << f << std::endl;
	return f;
}

float integrator::get_p_int()
{
	return p_int;
}

void integrator::reset_p_int()
{
	p_int = 0;
}



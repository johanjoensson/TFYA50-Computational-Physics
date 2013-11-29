#include "velocity_verlet_integration.h"

#include <iostream>	

integrator::integrator()
{
	h = 0;
	e_pot = 0;
	cutoff = 0;
	//p_int = 0;
}

void integrator::set_cutoff(float r)
{
	cutoff = r;
}

void integrator::set_timestep(float d)
{
	h = d;
}

void integrator::set_dimensions(float x, float y, float z)
{
	x_dim = x;
	y_dim = y;
	z_dim = z;
}

void integrator::set_sigma6(float sigma)
{
	float sigma3 = sigma*sigma*sigma;
	sig6 = sigma3*sigma3;
}
void integrator::set_epsilon(float epsilon)
{
	epsi = epsilon;
}

float integrator::get_epot()
{
	return e_pot;
}
void integrator::reset_epot()
{
	e_pot = 0;
}

/* Step 1 of the two step Velocity verlet algorithm. Updates only the position */
void integrator::verlet_integration_position(verlet_list particle)
{
	/* Update position of particle */
	vector_3d tmp = particle.data->pos;
	particle.data->pos += particle.data->vel*h + 0.5*particle.data->acc*h*h;
	tmp -= particle.data->pos;
	particle.data->incr_displacement(tmp.abs());
	/* Periodic boundary conditions */
	particle.data->pos.place(x_dim, y_dim, z_dim);
}

/* The second part of the Velocity verlet algorithm, updates velocity */
void integrator::verlet_integration_velocity(verlet_list particle)
{
	verlet_list *current = particle.next;
	vector_3d tmp_force = vector_3d(0,0,0);

	
	while(current != NULL){
		
		/* Calculate the vector between 2 atoms, with PBC */
		vector_3d r = particle.data->pos.diff(current->data->pos, x_dim, y_dim, z_dim);
		if(r*r < cutoff*cutoff){
			/* Update velocity and acceleration of the particle */
			tmp_force = calculate_force(particle.data, current->data);
//			particle.data->incr_next_acc(tmp_force/particle.data->mass);
//			current->data->decr_next_acc(tmp_force/current->data->mass);

			particle.data->decr_next_acc(tmp_force/particle.data->mass);
			current->data->incr_next_acc(tmp_force/current->data->mass);
		}
		current = current->next;
	}	
	
	particle.data->vel += 0.5*(particle.data->acc + particle.data->get_next_acc())*h;

	/* Scale velocities so that we don't leave the bulk in one single time step */
/*	vector_3d dist = h*particle.data->vel;
	int dx = (int)(dist.x/x_dim);
	int dy = (int)(dist.y/y_dim);
	int dz = (int)(dist.z/z_dim);

	vector_3d vel_diff(dx*x_dim/h, dy*y_dim/h, dz*z_dim/h);
	particle.data->vel -= vel_diff;
	if(dx != 0 || dy != 0 || dz != 0)
		System::Windows::Forms::MessageBox::Show("Whoa there!");
	/****************************************************************************/

	particle.data->update_acceleration();
}

vector_3d integrator::calculate_force(atom *atom_a, atom *atom_b)
{
	float ff=0;
	float sigma = 0.0017;
	vector_3d a = atom_a->pos;
	vector_3d b = atom_b->pos;
	vector_3d d = a.diff(b, x_dim, y_dim, z_dim);
	float r = a.distance(b, x_dim, y_dim, z_dim);
	float ri = 1/r;
	float ri2 = ri*ri;
	float ri6 = ri2*ri2*ri2;
	ff = 48*epsi*ri*sig6*(sig6*ri6*ri6-0.5*ri6)*0.964e-2;
	vector_3d f = d*ff*ri;
	float ecut = 4*ri6*epsi*sig6*(sig6*ri6-1);
	float ric3 = 1/(cutoff*cutoff*cutoff);
	/* accumulate the potential enegry */
	e_pot += -4*ric3*ric3*epsi*sig6*(sig6*ric3*ric3-1) + ecut;
	/* First part of internal pressure */
	p_int += d*f;

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

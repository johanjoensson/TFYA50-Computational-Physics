#include "atom.h"

atom::atom()
{
	pos = vector_3d(0,0,0);
	vel = vector_3d(0,0,0);
	acc = vector_3d(0,0,0);
	mass = 1;
	next_acc = vector_3d(0,0,0);
	displacement = 0;
}

atom::atom(vector_3d position, vector_3d velocity, vector_3d acceleration)
{
	pos = position;
	vel = velocity;
	acc = acceleration;
	next_acc = vector_3d(0,0,0);
	mass = 1;
	displacement = 0;
}

void atom::set_next_acc(vector_3d new_acc)
{
	next_acc = new_acc;
}

void atom::incr_next_acc(vector_3d new_acc)
{
	next_acc += new_acc;
}

void atom::decr_next_acc(vector_3d new_acc)
{
	next_acc -= new_acc;
}

vector_3d atom::get_next_acc()
{
	return next_acc;
}

void atom::update_acceleration()
{
	acc = next_acc;
	next_acc = vector_3d(0,0,0);
}

void atom::incr_displacement(float r)
{
	displacement += r;
}
void atom::zero_displacement()
{
	displacement = 0;
}

float atom::get_displacement()
{
	return displacement;
}

/*float atom::distance(vector_3d atom2_pos)
{
	if(abs(pos.x-atom2_pos.x) > 0.5*x_tot)
	{
		if(pos.x > atom2_pos.x)
			atom2_pos.x += x_tot;
		else
			atom2_pos.x -= x_tot;
	}
	if(abs(pos.y-atom2_pos.y) > 0.5*y_tot)
	{
		if(pos.y > atom2_pos.y)
			atom2_pos.y += y_tot;
		else
			atom2_pos.y -= y_tot;
	}	
	if(abs(pos.z-atom2_pos.z) > 0.5*z_tot)
	{
		if(pos.z > atom2_pos.z)
			atom2_pos.z += z_tot;
		else
			atom2_pos.z -= z_tot;
	}	
	vector_3d difference = pos-atom2_pos;
	float distance = difference*difference;
	return distance;
}*/
                                                 

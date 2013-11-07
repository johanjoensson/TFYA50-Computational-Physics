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
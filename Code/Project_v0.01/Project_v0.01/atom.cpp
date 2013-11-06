#include "atom.h"

atom::atom()
{
	pos = vector_3d(0,0,0);
	vel = vector_3d(0,0,0);
	acc = vector_3d(0,0,0);
}

atom::atom(vector_3d position, vector_3d velocity, vector_3d acceleration)
{
	pos = position;
	vel = velocity;
	acc = acceleration;
}
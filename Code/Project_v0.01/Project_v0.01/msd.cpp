#include "msd.h"
#include "atom.h"
#include <iostream>

/*
*a is the atom that is choosen
*i is wich atom the user wants to look at
*N is the number off atoms in the world
*/
float msd(atom::atom a, int N){
	vector_3d R = a.pos.diff(a.orig_pos, x_tot, y_tot, z_tot);
	r=(R*R)/N;
	return(r);
}
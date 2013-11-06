#include "world.h"
#include "iostream"

#ifndef NULL
#define NULL 0
#endif

world::world()
{
	cutoff = 0;
	N = 0;
	atoms = NULL;
	bulk = NULL;
}


/* A simple and stupid constructor, takes the number of atoms to be created only */
/* TODO: Add proper constructor that is actually useful */
world::world(unsigned int n)
{
	cutoff = 100;
	verlet_integrator = integrator();
	N = n;

	/* Create all the atoms */
	/* Currently all atoms are placed in origin, with velocity and acceleration equal to zero */
	atoms = new atom[n];

	/* Create the list of verlet lists */
	bulk = new verlet_list[n];

	/* Link each cell in the array of verlet lists to the corresponding atom */
	for(int i = 0; i < n; i++){
		bulk[i].data = &atoms[i];
		bulk[i].set_verlet_skin(1.5*cutoff);
	}
}


world::world(unsigned int x, unsigned int y, unsigned int z, float a) 
{
	N = x*y*z+(x-1)*(y-1)*(z-1); //Number of atoms in total in a bcc crystal based on a x*y*z cubic lattice;

	atoms = new atom[N];
	
	/* Adding atoms in bcc-lattice */
	int n = 0;	//atom count
	for(unsigned int i = 0; i < x; i++){
		for(unsigned int j = 0; j < y; j++){
			for(unsigned int k = 0; k < z; k++){

				atoms[n] = atom(vector_3d(a*i, a*j, a*k), vector_3d(), vector_3d());
				n++;
				if(i<x && j<y && k<z){	//add body atom if inside bulk
					atoms[n] = atom(vector_3d(a*(i+0.5), a*(j+0.5), a*(k+0.5)), vector_3d(), vector_3d());
					n++;
				}
			}
		}
	}

	/* Create the list of verlet lists */
	bulk = new verlet_list[N];

	/* Link each cell in the array of verlet lists to the corresponding atom */
	for(int i = 0; i < N; i++){
		bulk[i].data = &atoms[i];
	}
}


void world::update_verlet_lists()
{
	for(int i = 0; i < this->N; i++){
		for(int j = i + 1; j < this->N; j++){
			this->bulk[i].add_atom(this->bulk[j]);
			/* This might seem like a good optimization, but it will lead to double counting of force, if you "optimize" that part */
//			this->bulk[j].add_atom(this->bulk[i]);
		}
	}
}
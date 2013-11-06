#include "world.h"
#include "iostream"

#ifndef NULL
#define NULL 0
#endif

world::world()
{
	N = 0;
	atoms = NULL;
	bulk = NULL;
}



world::world(unsigned int n)
{
	N = n;

	/* Create all the atoms */
	/* Currently all atoms are placed in origin, with velocity and acceleration equal to zero */
	atoms = new atom[n];

	/* Create the list of verlet lists */
	bulk = new verlet_list[n];

	/* Link each cell in the array of verlet lists to the corresponding atom */
	for(int i = 0; i < n; i++){
		bulk[i].data = &atoms[i];
	}
}


world::world(unsigned int x, unsigned int y, unsigned int z, float a) 
{
	N = x*y*z+(x-1)*(y-1)*(z-1); //Number of atoms in total in a bcc crystal based on a x*y*z cubic lattice;

	atoms = new atom[N];
	
	/* Adding atoms in bcc-lattice */
	int n = 0;	//atom count
	for(int a = 0; a < x; a++){
		for(int b = 0; b < y; b++){
			for(int c = 0; c < z; c++){

				atoms[n] = atom(vector_3d(a*x, a*y, a*z), vector_3d(), vector_3d());
				n++;
				if(a<x && b<y && c<z){	//add body atom if inside bulk
					atoms[n] = atom(vector_3d(a*(x+0.5), a*(y+0.5), a*(z+0.5)), vector_3d(), vector_3d());
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
			this->bulk[j].add_atom(this->bulk[i]);
		}
	}
}

void test_bcc_positions()
{
	
	unsigned int x = 5;
	unsigned int y = 5;
	unsigned int z = 5;
	float a = 1;

	world w(x, y, z, a);

	std::cout << "xpos" << w.atoms[1].pos.x;
}
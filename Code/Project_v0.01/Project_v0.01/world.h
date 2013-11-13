#include "atom.h"
#include "verlet_list.h"
#include "velocity_verlet_integration.h"

enum type_of_average
{
	KINETIC_ENERGY,
	POTENTIAL_ENERGY,
	TEMPERATURE,
	MSD
};

enum crystalStructure
{
	BCC,
	FCC,
	DIAMOND,
	UNKNOWN,
};

class world{
private:
	float cutoff;
public:
	world();
	world(unsigned int n);
	world(unsigned int x, unsigned int y, unsigned int z, float a, crystalStructure type);

	void set_cutoff(float r);

	integrator verlet_integrator;
	unsigned int N;
	atom *atoms;
	verlet_list *bulk;
	float x_tot;        // Total length of the crystal for the respective axes
	float y_tot;
	float z_tot;

	void update_verlet_lists();
	void world_2(unsigned int x, unsigned int y, unsigned int z, float a);
	
/*
*a is the atom that is choosen
*N is the number off atoms in the world
*/
	float msd(atom a, int N);
	
/*
*The debye temprature is returned as in the design (theta_D)^2
*msd is the mean square displacement, T is the temprature and 
*m is the mass for one atom.
*/
	float debye_temp(float msd, float T, float m);

/*
*N is here the total number of atoms
*totEnergy is the total energy (kinetic + potential)
*In the original equation the energy of the fre atom is included
*but that shoudn't be nessesary.
*/
	float cohEnergy (int N, float totEnergy);
};


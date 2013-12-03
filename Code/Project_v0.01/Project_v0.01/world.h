#ifndef WORLD_H
#define WORLD_H

#include "atom.h"
#include "verlet_list.h"
#include "velocity_verlet_integration.h"
#include "output.h"


/* ************ Natural Constants ************ */
#define kB 1.3806488e-23 /*Boltzmann's Constant in SI units*/ //kB 8.6173324e-5 /* Boltzmann's Constant [eV/K] */
//#define kB_T 8.6173324e-5
#define hBar 6.5821189e-1 /* plancks constant/2pi [ev*fs] */
#define atomic_u 1.66055389e-27

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
	unsigned int start_time;
	float time_step;
	float cutoff;
	float E_kin;
	float E_kin_sqr;
	float r_msd;
	float T;
	float P;
	float C_v;
	float collision_rate;
	float T_start;
	float epsilon;
	float sigma;

	bool visualise;
	bool thermostat;

	PBC boundary;


	outputter writer;

	void init();

	void calc_temperature(float E_kin, int N);
	void calc_pressure(float p_sum, int N, float V);
	void calc_specific_heat(float E_kin, float E_kin_sqr, int N);

public:
	world();
	world(unsigned int n);
	world(unsigned int n, float x_dim, float y_dim, float z_dim, float temp);
	world(unsigned int x, unsigned int y, unsigned int z, float a, float mass, float temp, crystalStructure type, int t_stop, int t_start, PBC conditions);
	void unset_world();
	float SI_natural(float arg, char quantity, int SI, char in_prefix, char out_prefix);

	void set_cutoff(float r);
	void set_timestep(float h);
	void toggle_visualisation();
	void set_collision_rate(float f);
	void set_thermostat(bool val);
	void set_visualisation(bool val);
	void set_sigma(float sig);
	void set_epsilon(float epsi);
	void set_boundary(PBC conditions);
	void set_times(unsigned int start, unsigned int stop, float ts);

	void set_intervals(unsigned int store, unsigned int vis);

	float get_sigma();
	float get_epsilon();
	float get_collision_rate();
	PBC get_PBC();
	float get_cutoff();
	bool get_thermostat();
	float get_T_start();

	integrator verlet_integrator;
	unsigned int N;
	atom *atoms;
	verlet_list *bulk;
	float x_tot;        // Total length of the crystal for the respective axes
	float y_tot;
	float z_tot;
	float V; //Volume

	unsigned int t_end;
	unsigned int t_start;

	unsigned int vis_interval;
	unsigned int storage_interval;

	void kinetic_energy(atom a);
	void kinetic_energy();
	float get_kinetic_energy();
	float get_kinetic_energy_squared();
	void update_verlet_lists();
	void update_verlet_list(int i);
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


	void bccSetup(unsigned int x, unsigned int y, unsigned int z, float a);
	void fccSetup(unsigned int x, unsigned int y, unsigned int z, float a);
	void diamondSetup(unsigned int x, unsigned int y, unsigned int z, float a);
	void back2bak_store();

	void integrate();
};

#endif /* WORLD_H */


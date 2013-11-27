#include "atom.h"
#include "verlet_list.h"
#include "velocity_verlet_integration.h"
#include "output.h"

/* ************ Natural Constants ************ */
#define kB 1.3806488e-23 /*Boltzmann's Constant in SI units*/ //kB 8.6173324e-5 /* Boltzmann's Constant [eV/K] */
#define hBar 6.5821189e-1 /* plancks constant/2pi [ev*fs] */


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

	bool visualise;
	bool thermostat;


	outputter writer;

	void init();

	void calc_temperature(float E_kin, int N);
	void calc_pressure(float p_sum, int N, float V);
	void calc_specific_heat(float E_kin, float E_kin_sqr, int N);

public:
	world();
	world(unsigned int n);
	world(unsigned int x, unsigned int y, unsigned int z, float a, float mass, float temp, crystalStructure type);
	void unset_world();
	float SI_natural(float arg, char quantity, int SI, char in_prefix, char out_prefix);

	void set_cutoff(float r);
	void set_timestep(float h);
	void toggle_visualisation();
	void set_collision_rate(float f);
	void set_thermostat(bool val);
	void set_visualisation(bool val);

	void set_sigma(float sigma);
	void set_epsilon(float epsilon);

	integrator verlet_integrator;
	unsigned int N;
	atom *atoms;
	verlet_list *bulk;
	float x_tot;        // Total length of the crystal for the respective axes
	float y_tot;
	float z_tot;
	float V; //Volume

	void kinetic_energy(atom a);
	void kinetic_energy();
	float get_kinetic_energy();
	float get_kinetic_energy_squared();
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


	void bccSetup(unsigned int x, unsigned int y, unsigned int z, float a);
	void fccSetup(unsigned int x, unsigned int y, unsigned int z, float a);
	void diamondSetup(unsigned int x, unsigned int y, unsigned int z, float a);

	void integrate(unsigned int t_end);
};


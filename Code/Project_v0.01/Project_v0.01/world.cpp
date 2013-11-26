#include "world.h"

#include "Form1.h"

#include <random>

#include <sstream>


#ifndef NULL
#define NULL 0
#endif


world::~world()
{
	delete[] bulk;
	delete[] atoms;
}

world::world()
{
	cutoff = 0;
	N = 0;
	atoms = NULL;
	bulk = NULL;
	x_tot = 0;
	y_tot = 0;
	z_tot = 0;
	V = x_tot*y_tot*z_tot;
//	writer = outputter("toto.txt", "titi.txt");
}

void world::init()
{
	cutoff = 0;
	start_time = 0;
	time_step = 0;
	E_kin = 0;
	E_kin_sqr = 0;
	r_msd = 0;
	T = 0;
	P = 0;
	C_v = 0;

	visualise = false;
	thermostat = false;

	verlet_integrator = integrator();
}

/* A simple and stupid constructor, takes the number of atoms to be created only */
world::world(unsigned int n)
{
	init();
	cutoff = 100;
	verlet_integrator = integrator();
	verlet_integrator.set_cutoff(cutoff);

	N = n;
	x_tot = 1;
	y_tot = 1;
	z_tot = 1;
	V = x_tot*y_tot*z_tot;

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


/* 
set positions for all atoms in structure
x,y,z = a = lattice constant, type = type of crystal structure (BCC or FCC or Diamond)
*/
world::world(unsigned int x, unsigned int y, unsigned int z, float a, float mass, float temp, enum crystalStructure type)	
{

	init();
	x_tot = x*a;
	y_tot = y*a;
	z_tot = z*a;
	V = x_tot*y_tot*z_tot;
	verlet_integrator.set_dimensions(x_tot, y_tot, z_tot);
	switch (type)
	{
	case BCC:
		world::bccSetup(x, y, z, a);
		break;

	case FCC:
		fccSetup(x, y, z, a);
		break;

	case DIAMOND:
		diamondSetup(x, y, z, a);
		break;

	default:
		std::cout << "Error: false crystal structure" << std::endl;
		break;
	}

	/* Create the list of verlet lists */
	bulk = new verlet_list[N];

	/* Link each cell in the array of verlet lists to the corresponding atom 
	 * Set the mass of each atom, calculate the velocity of the centre of mass and
	 * the sum of the squares of all the velocities */
	vector_3d sum_vel = vector_3d(0,0,0);
	float sum_vel2 = 0;
	for(int i = 0; i < N; i++){
		atoms[i].mass = mass;
		sum_vel += atoms[i].vel;
		sum_vel2 += atoms[i].vel*atoms[i].vel;

		bulk[i].data = &atoms[i];
	}
	
	/* Scale the centre of mass velocity */
	sum_vel /= N;
	sum_vel2 /= N;
	T_start = temp;
	float scale_factor = sqrt(3*kB*temp/sum_vel2);
	for(unsigned int i = 0; i < N; i++){
		atoms[i].vel = (atoms[i].vel - sum_vel)*scale_factor;
	}
	verlet_integrator.set_dimensions(x*a, y*a, z*a);
}

void world::set_timestep(float h)
{
	time_step = h;
	verlet_integrator.set_timestep(h);
}

void world::set_cutoff(float r)
{
	cutoff = r;
	verlet_integrator.set_cutoff(r);
	for(int i = 0; i < this->N; i++){
		this->bulk[i].set_verlet_skin(1.5*cutoff);
	}
}

void world::toggle_visualisation()
{
	visualise = !visualise;
}

void world::set_visualisation(bool val)
{
	visualise = val;
}

void world::set_thermostat(bool val)
{
	thermostat = val;
}

void world::set_collision_rate(float f){
	collision_rate = f;
}

void world::set_sigma(float sigma)
{
	this->verlet_integrator.set_sigma6(sigma);
}
void world::set_epsilon(float epsilon)
{
	this->verlet_integrator.set_epsilon(epsilon);
}

void world::update_verlet_lists()
{
	for(int i = 0; i < this->N; i++){
		this->bulk[i].data->zero_displacement();
		for(int j = i + 1; j < this->N; j++){
			this->bulk[i].add_atom(this->bulk[j]);
		}
	}
}

void world::kinetic_energy()
{
	E_kin = 0;
	E_kin_sqr = 0;
}

void world::kinetic_energy(atom a)
{
	float temp = a.mass*a.vel*a.vel;
	E_kin += temp;
	E_kin_sqr += temp*temp;
}


float world::get_kinetic_energy()
{
	return E_kin;
}

float world::get_kinetic_energy_squared()
{
	return E_kin_sqr;
}

float world::msd(atom a, int N)
{
	vector_3d R = a.pos.diff(a.orig_pos, x_tot, y_tot, z_tot);
	float r=(R*R)/N;
	return(r);
}

float world::debye_temp(float msd, float T, float m)
{
	float theta_D = (3*hBar*T)/(m*kB*msd);
	return(theta_D);
}

float world::cohEnergy (int N, float totEnergy)
{
	float cE = totEnergy/N;
	return(cE);
}

void world::bccSetup(unsigned int x, unsigned int y, unsigned int z, float a)
{
	int n = 0;	//atom count
//	N = x*y*z+(x-1)*(y-1)*(z-1); //Number of atoms in total in a bcc crystal based on a x*y*z cubic lattice;
	N = x*y*z*2;

	atoms = new atom[N];
	
	/* Adding atoms in bcc-lattice
	x,y,z = number of cells in each direction*/

	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			for(int k = 0; k < z; k++){
				float xpos = a*i;
				float ypos = a*j;
				float zpos = a*k;
				/*Add two-atom basis*/
				atoms[n] = atom(vector_3d(xpos, ypos, zpos));
				n++;
				atoms[n] = atom(vector_3d(xpos+0.5*a, ypos+0.5*a, zpos+0.5*a));
				n++;
			}
		}
	}
}


void world::fccSetup(unsigned int x, unsigned int y, unsigned int z, float a)
{
	int n = 0;	//atom count
	//N = x*y*z+(x-1)*y*(z-1)+x*(y-1)*(z-1)+(x-1)*(y-1)*z; //number of atoms in a x*y*z fcc lattice structure
	N = x*y*z*4; //4 atoms in each cell
	
	atoms = new atom[N];

	/* Go trough all cells */
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			for(int k = 0; k < z; k++){

				float xpos = a*i;
				float ypos = a*j;
				float zpos = a*k;

				/*one corner atom for each cell*/
				atoms[n] = atom(vector_3d(xpos, ypos, zpos));
				n++;
				/*three face atoms for each cell */
				atoms[n] = atom(vector_3d(xpos,ypos+a/2,zpos+a/2));
				n++;
				atoms[n] = atom(vector_3d(xpos+a/2,ypos,zpos+a/2));
				n++;
				atoms[n] = atom(vector_3d(xpos+a/2,ypos+a/2,zpos));
				n++;
/*				

				if(i==x && j<y && k<z){
//					atoms[n] = atom(vector_3d(xpos,ypos+a/2,zpos+a/2), vector_3d(), vector_3d());
					atoms[n] = atom(vector_3d(xpos,ypos+a/2,zpos+a/2));
					n++;
				}
				if(i<x && j==y && k<z){
//					atoms[n] = atom(vector_3d(xpos+a/2,ypos,zpos+a/2), vector_3d(), vector_3d());
					atoms[n] = atom(vector_3d(xpos+a/2,ypos,zpos+a/2));
					n++;
				}

				if(i<x && j<y && k==z){
//					atoms[n] = atom(vector_3d(xpos+a/2,ypos+a/2,zpos), vector_3d(), vector_3d());
					atoms[n] = atom(vector_3d(xpos+a/2,ypos+a/2,zpos));
					n++;
				}
*/			
			}
		}
	}	

}



void world::diamondSetup(unsigned int x, unsigned int y, unsigned int z, float a)
{
	int n = 0;	//atom count
	N = x*y*z*8;

	atoms = new atom[N];
	
	/* Adding atoms in fcc-lattice */
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			for(int k = 0; k < z; k++){

				float xpos = a*i;
				float ypos = a*j;
				float zpos = a*k;

				/*one corner atom for each cell*/
				atoms[n] = atom(vector_3d(xpos, ypos, zpos));
				n++;
				/*three face atoms for each cell */
				atoms[n] = atom(vector_3d(xpos,ypos+a/2,zpos+a/2));
				n++;
				atoms[n] = atom(vector_3d(xpos+a/2,ypos,zpos+a/2));
				n++;
				atoms[n] = atom(vector_3d(xpos+a/2,ypos+a/2,zpos));
				n++;
					
				/* Adding four extra diamond structure atoms in each fcc cell*/ 
				atoms[n] = atom(vector_3d(xpos+3*a/4,ypos+3*a/4,zpos+3*a/4));
				n++;
				atoms[n] = atom(vector_3d(xpos+3*a/4,ypos+a/4,zpos+a/4));
				n++;
				atoms[n] = atom(vector_3d(xpos+a/4,ypos+3*a/4,zpos+a/4));
				n++;
				atoms[n] = atom(vector_3d(xpos+a/4,ypos+a/4,zpos+3*a/4));
				n++;
			}
		}
	}
}

void world::calc_temperature(float E_kin, int N) //Temperature
{
	T = E_kin / (3.0*kB*N);
}

void world::calc_pressure(float p_sum, int N, float V) //internal pressure
{
	P = N*kB*T/V + 1/(6*V)* p_sum;
}

void world::calc_specific_heat(float E_kin, float E_kin_sqr, int N)
{
	C_v = 3*N*kB/(2-4*N*(E_kin_sqr - E_kin*E_kin)/(3*E_kin*E_kin));
}

void world::integrate(unsigned int t_end)
{
	float max_disp = 0;
	float data[10];

	this->update_verlet_lists();

	/* Store the initial positions of all atoms */
	for(unsigned int i = 0; i < this->N; i++){
		writer.store_atom(*this->bulk[i].data);
	}

	float collisionTest = 0;
	float sigma = sqrt(T_start);
	std::default_random_engine generator;
	std::normal_distribution<float> gauss(T_start,sigma);
	float collision_val = collision_rate*time_step*1e-15;

	for(unsigned int t = 0; t < t_end; t++){
		this->verlet_integrator.reset_p_int();
		this->verlet_integrator.reset_epot();
		this->kinetic_energy();
		this->r_msd = 0;

		/* First part of Verlet integration */
		for(int i = 0; i < this->N; i++){
			this->verlet_integrator.verlet_integration_position(this->bulk[i]);
			this->r_msd += this->msd(this->atoms[i], this->N);

			if(this->bulk[i].data->get_displacement() > max_disp){
				max_disp = this->bulk[i].data->get_displacement();
			}
			if(visualise)
			{
				writer.store_atom(*this->bulk[i].data);
			}
		}
		/* Second part of Verlet integration */
		for(int i = 0; i < this->N; i++){
			this->verlet_integrator.verlet_integration_velocity(this->bulk[i]);
			this->kinetic_energy(this->atoms[i]);
		}

		/* Andersen thermostat */
		
		if(thermostat){
			for(int i = 0; i < this->N; i++){
				collisionTest = rand();
				if(collisionTest  < collision_val){
					this->atoms[i].vel = vector_3d(gauss(generator),gauss(generator),gauss(generator));
				}
			}
		}

		calc_temperature(this->get_kinetic_energy(), this->N);
		calc_pressure(this->verlet_integrator.get_p_int(), this->N, this->V);
		calc_specific_heat(this->get_kinetic_energy(), this->get_kinetic_energy_squared(), this->N);

		data[0] = t*time_step;
		data[1] = this->get_kinetic_energy();
		data[2] = this->verlet_integrator.get_epot();
		data[3] = this->get_kinetic_energy() + this->verlet_integrator.get_epot();
		data[4] = data[3]/this->N;
		data[5] = r_msd;
		data[6] = P;
		data[7] = T;
		data[8] = this->debye_temp(r_msd, T, atoms[0].mass);
		data[9] = this->cohEnergy(this->N, (this->verlet_integrator.get_epot()+0.5*this->get_kinetic_energy()));

		writer.store_data(data);
		
			
		if(max_disp > 0.5*cutoff){
			for(unsigned int i = 0; i < this->N; i++){
				this->bulk[i].clear_verlet_list();
			}
			max_disp = 0;
			this->update_verlet_lists();
		}
	}
}

float SI_natural(float arg, char quantity, int SI, char in_prefix, char out_prefix)
{
	float in_scaling = 1;
	float out_scaling = 1;
	
	switch(quantity)
	{
		case 'E':
			if(SI == 1)
				arg /= 1.6021773e-19;
			else
				arg *= 1.6021773e-19;
			break;

		case 'l':
			if(SI == 1)
				arg /= 1.9732705e-7;
			else
				arg *= 1.9732705e-7;
			break;

		case 'v':
			if(SI == 1)
				arg /= 2.99792458e8;
			else
				arg *= 2.99792458e8;
			break;

		case 'a':
			if(SI == 1)
				arg /= 4.5546490065e23;
			else
				arg *= 4.5546490065e23;
			break;

		case 'm': //This unit is not SI, conversion is between u and eV!
			if(SI == 1)
				arg *= 931494061;
			else
				arg /= 931494061;
			break;

		case 'F':
			if(SI == 1)
				arg /= 8.119403e-13;
			else
				arg *= 8.119403e-13;
			break;

		case 't':
			if(SI == 1)
				arg /= 6.5821220e-16;
			else
				arg *= 6.5821220e-16;
			break;

		case 'p':
			if(SI == 1)
				arg /= 5.3442883e-28;
			else
				arg *= 5.3442883e-28;
			break;

		case 'T':
			if(SI == 1)
				arg /= 11604.5629;
			else
				arg *= 11604.5629;
			break;

		default:
			return arg;
			break;
	}

	for(int i=0; i<2; i++)
	{
		char temp_char = 'I';
		float temp;
		if(i==0)
			char temp = in_prefix;
		else
			char temp = out_prefix;
		switch (temp_char)
		{
		case 'I': break;

		case 'd': //Ångström
			temp = 1e-10;
			break;
		
			case 'Y': 
				temp = 1e24;
				break;
			case 'Z': 
				temp = 1e21;
				break;
			case 'E': 
				temp = 1e18;
				break;
			case 'P': 
				temp = 1e15;
				break;
			case 'T': 
				temp = 1e12;
				break;
			case 'G': 
				temp = 1e9;
				break;
			case 'M': 
				temp = 1e6;
				break;
			case 'k': 
				temp = 1e3;
				break;
			case 'm': 
				temp = 1e-3;
				break;
			case 'c': //Micro
				temp = 1e-6;
				break;
			case 'n': 
				temp = 1e-9;
				break;
			case 'p': 
				temp = 1e-12;
				break;
			case 'f': 
				temp = 1e-15;
				break;
			case 'a': 
				temp = 1e-18;
				break;
			case 'z': 
				temp = 1e-21;
				break;
			case 'y': 
				temp = 1e-24;
				break;
			default: break;
		}
		if(i == 0)
			in_scaling = temp;
		else
			out_scaling = temp;
	}

	arg *= in_scaling/out_scaling;
	return arg;
}
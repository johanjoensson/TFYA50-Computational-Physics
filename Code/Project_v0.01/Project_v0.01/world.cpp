#include "world.h"
#include <iostream>

#ifndef NULL
#define NULL 0
#endif

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
}

/* A simple and stupid constructor, takes the number of atoms to be created only */
/* TODO: Add proper constructor that is actually useful */
world::world(unsigned int n)
{
	cutoff = 100;
	verlet_integrator = integrator();
	verlet_integrator.set_cutoff(cutoff);
//	std::cout << "Set number of atoms to: " << n << std::endl;
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
x,y,z = a = lattice constant, type = type of crystal structure (BCC or FCC)
*/
world::world(unsigned int x, unsigned int y, unsigned int z, float a, enum crystalStructure type)	
{

	verlet_integrator = integrator();
	verlet_integrator.set_cutoff(3*a);
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

	/* Link each cell in the array of verlet lists to the corresponding atom */
	for(int i = 0; i < N; i++){
		bulk[i].data = &atoms[i];
		bulk[i].set_verlet_skin(5);
	}
}

void world::set_cutoff(float r)
{
	cutoff = r;
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
	float k_b = .0000861734;
	float theta_D = (3*T)/(m*k_b*msd);
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
	N = x*y*z+(x-1)*(y-1)*(z-1); //Number of atoms in total in a bcc crystal based on a x*y*z cubic lattice;
	x_tot = x*a;
	y_tot = y*a;
	z_tot = z*a;

	atoms = new atom[N];
	
	/* Adding atoms in bcc-lattice */
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			for(int k = 0; k < z; k++){
				float xpos = a*i;
				float ypos = a*j;
				float zpos = a*k;
				atoms[n] = atom(vector_3d(xpos, ypos, zpos), vector_3d(), vector_3d());
				n++;
			
				if(i<(x-1) && j<(y-1) && k<(z-1)){	//add body atom if inside bulk
					atoms[n] = atom(vector_3d(xpos+0.5*a, ypos+0.5*a, zpos+0.5*a), vector_3d(0,0,0), vector_3d(0,0,0));
					n++;
				}
			}
		}
	}
}

void world::fccSetup(unsigned int x, unsigned int y, unsigned int z, float a)
{
	int n = 0;	//atom count
	N = x*y*z+(x-1)*y*(z-1)+x*(y-1)*(z-1)+(x-1)*(y-1)*z; //number of atoms in a x*y*z fcc lattice structure
	atoms = new atom[N];

	/* Adding atoms in fcc-lattice */
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			for(int k = 0; k < z; k++){

				float xpos = a*i;
				float ypos = a*j;
				float zpos = a*k;
				atoms[n] = atom(vector_3d(xpos, ypos, zpos), vector_3d(), vector_3d());
				n++;

				if(i<(x-1) && j<(y-1) && k<(z-1)){
					atoms[n] = atom(vector_3d(xpos,ypos+a/2,zpos+a/2), vector_3d(), vector_3d());
					n++;
					atoms[n] = atom(vector_3d(xpos+a/2,ypos,zpos+a/2), vector_3d(), vector_3d());
					n++;
					atoms[n] = atom(vector_3d(xpos+a/2,ypos+a/2,zpos), vector_3d(), vector_3d());
					n++;
				}

				if(i==(x-1) && j<(y-1) && k<(z-1)){
					atoms[n] = atom(vector_3d(xpos,ypos+a/2,zpos+a/2), vector_3d(), vector_3d());
					n++;
				}
				if(i<(x-1) && j==(y-1) && k<(z-1)){
					atoms[n] = atom(vector_3d(xpos+a/2,ypos,zpos+a/2), vector_3d(), vector_3d());
					n++;
				}

				if(i<(x-1) && j<(y-1) && k==(z-1)){
					atoms[n] = atom(vector_3d(xpos+a/2,ypos+a/2,zpos), vector_3d(), vector_3d());
					n++;
				}
			
			}
		}
	}	

}



void world::diamondSetup(unsigned int x, unsigned int y, unsigned int z, float a)
{
	int n = 0;	//atom count
	N = x*y*z+(x-1)*y*(z-1)+x*(y-1)*(z-1)+(x-1)*(y-1)*z+4*(x-1)*(y-1)*(z-1); //number of atoms in a x*y*z fcc lattice structure

	atoms = new atom[N];
	
	/* Adding atoms in fcc-lattice */
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			for(int k = 0; k < z; k++){
				float xpos = a*i;
				float ypos = a*j;
				float zpos = a*k;
				atoms[n] = atom(vector_3d(xpos, ypos, zpos), vector_3d(), vector_3d());
				n++;
			
				if(i<(x-1) && j<(y-1) && k<(z-1)){
					atoms[n] = atom(vector_3d(xpos,ypos+a/2,zpos+a/2), vector_3d(), vector_3d());
					n++;
					atoms[n] = atom(vector_3d(xpos+a/2,ypos,zpos+a/2), vector_3d(), vector_3d());
					n++;
					atoms[n] = atom(vector_3d(xpos+a/2,ypos+a/2,zpos), vector_3d(), vector_3d());
					n++;
					
					/* Adding extra diamond structure atoms in fcc cells*/
					atoms[n] = atom(vector_3d(xpos+a/4,ypos+a/4,zpos+a/4), vector_3d(), vector_3d());
					n++;
					atoms[n] = atom(vector_3d(xpos+3*a/4,ypos+a/4,zpos+a/4), vector_3d(), vector_3d());
					n++;
					atoms[n] = atom(vector_3d(xpos+a/4,ypos+3*a/4,zpos+3*a/4), vector_3d(), vector_3d());
					n++;
					atoms[n] = atom(vector_3d(xpos+3*a/4,ypos+3*a/4,zpos+3*a/4), vector_3d(), vector_3d());
					n++;
				}

				if(i==(x-1) && j<(y-1) && k<(z-1)){
					atoms[n] = atom(vector_3d(xpos,ypos+a/2,zpos+a/2), vector_3d(), vector_3d());
					n++;
				}
				if(i<(x-1) && j==(y-1) && k<(z-1)){
					atoms[n] = atom(vector_3d(xpos+a/2,ypos,zpos+a/2), vector_3d(), vector_3d());
					n++;
				}

				if(i<(x-1) && j<(y-1) && k==(z-1)){
					atoms[n] = atom(vector_3d(xpos+a/2,ypos+a/2,zpos), vector_3d(), vector_3d());
					n++;
				}
			
			}
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

		case 'm':
			if(SI == 1)
				arg /= 1.7826627e-36;
			else
				arg *= 1.7826627e-36;
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

		default:
			arg = 1337;
			break;
	}

	for(int i=0; i<2; i++)
	{
		char temp = 'F';
		if(i==0)
			char temp = in_prefix;
		else
			char temp = out_prefix;
		switch (temp)
		{
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
			case 'd': //Ångström
				temp = 1e-10;
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

#include "world.h"

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

	verlet_integrator = integrator();
}

/* A simple and stupid constructor, takes the number of atoms to be created only */
world::world(unsigned int n)
{
	init();
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

	init();
	x_tot = x*a;
	y_tot = y*a;
	z_tot = z*a;
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
//	float k_b = .0000861734;
	float theta_D = (3*T)/(m*kB*msd);
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

void world::calc_temperature(float E_kin, int N) //Temperature
{
	T = E_kin / (3.0*kB*N);
}

void world::calc_pressure(float p_sum, int N, float V) //internal pressure
{
	P = N*kB*T/V + p_sum;
}

void world::calc_specific_heat(float E_kin, float E_kin_sqr, int N)
{
	C_v = 3*N*kB/(2-4*N*(E_kin_sqr - E_kin*E_kin)/(3*E_kin*E_kin));
}

void world::integrate(unsigned int t_end)
{
	float max_disp = 0;
	float data[10];
	for(unsigned int t = 0; t < t_end; t++){
		this->verlet_integrator.reset_p_int();
		this->kinetic_energy();
		this->r_msd = 0;

		/* First part of Verlet integration */
		for(int i = 0; i < this->N; i++){
			this->verlet_integrator.verlet_integration_position(this->bulk[i]);
			this->r_msd += this->msd(this->atoms[i], this->N);

			if(this->bulk[i].data->get_displacement() > max_disp){
				max_disp = this->bulk[i].data->get_displacement();
			}
		}
		/* Second part of Verlet integration */
		for(int i = 0; i < this->N; i++){
			this->verlet_integrator.verlet_integration_velocity(this->bulk[i]);
			this->kinetic_energy(this->atoms[i]);
		}

		calc_temperature(this->get_kinetic_energy(), this->N);
		calc_pressure(this->verlet_integrator.get_p_int(), this->N, this->V);
		calc_specific_heat(this->get_kinetic_energy(), this->get_kinetic_energy_squared(), this->N);

		data[0] = t*time_step;
		data[1] = this->get_kinetic_energy();
		data[2] = this->verlet_integrator.e_pot;
		data[3] = this->get_kinetic_energy() + this->verlet_integrator.e_pot;
		data[4] = data[3]/this->N;
		data[5] = r_msd;
		data[6] = P;
		data[7] = T;
		data[8] = this->debye_temp(r_msd, 50, 1);
		data[9] = this->cohEnergy(this->N, (this->verlet_integrator.e_pot+0.5*this->get_kinetic_energy()));

		writer.store_data(data);
		for(unsigned int i = 0; i < this->N; i++){
			writer.store_atom(*this->bulk[i].data);
		}
			
		if(max_disp > 0.5*cutoff){
			for(unsigned int i = 0; i < this->N; i++){
				this->bulk[i].clear_verlet_list();
			}
			max_disp = 0;
			this->update_verlet_lists();
		}
	}

}

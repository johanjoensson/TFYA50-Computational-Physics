#include "vector_lib.h"
#include "world.h"
#include "verlet_list.h"
#include "output.h"
#include <iostream>
//#include <cstdlib>
//#include <pthread.h>

using namespace std;

/* ************ Natural Constants ************ */
#define kB 8.6173324e-5 /* Boltzmann's Constant [eV/K] */

/* ************ -Global Variables- ************ */
float x_tot; /* Total length of the crystal [1/eV] */
float y_tot;
float z_tot;
float P; /* Internal Pressure [eV^4] */
float T; /* Temperature [K] */
float C_v; /* Specific Heat [eV/K] */

/* ************ ----Functions---- ************ */
void calc_temperature(float E_kin, int N);
void calc_pressure(float p_sum, int N, float V);
void calc_specific_heat(float E_kin, float E_kin_sqr, int N);

int main()
{
	world test(5,5,2,0.1,BCC);
	outputter writer("toto.txt", "titi.txt");

//	std::cout << "Total number of particles: " << test.N << std::endl;
/*	
 	test.bulk[0].data->pos = vector_3d(1.0, 0.0, 0.0);
	test.bulk[1].data->pos = vector_3d(0.0, 1.0, 0.0);
	test.bulk[2].data->pos = vector_3d(0.0, 0.0, 1.0);
	test.bulk[3].data->pos = vector_3d(1.0, 0.0, 1.0);

	test.bulk[0].data->acc = vector_3d(25.0, 0.0, 1.0);
	test.bulk[1].data->vel = vector_3d(3.0, 0.0, 0.0);
	test.bulk[2].data->vel = vector_3d(1.0, 0.4, 1.2);
	test.bulk[3].data->vel = vector_3d(1.0, 1.0, 0.0);
	test.bulk[4].data->vel = vector_3d(0.1, 0.3, 0.3);
*/

	x_tot = test.x_tot;
	y_tot = test.y_tot;
	z_tot = test.z_tot;

	verlet_list *current;
	test.update_verlet_lists();

	float data[10];

	float t_max = 2000;
	float timestep = 0.0000002;
	float cutoff = 0.05;

	float max_disp = 0;
	for(unsigned int t = 0; t < t_max; t++){
		/* Move system to next time step */
		test.verlet_integrator.reset_p_int();
		test.kinetic_energy();
		float r_msd = 0;
		for(unsigned int i = 0; i < test.N; i++){

//			std::cout << test.bulk[i].data->pos << "\t";
			test.verlet_integrator.verlet_integration_position(test.bulk[i]);

			r_msd += test.msd(test.atoms[i], test.N);

			if(test.bulk[i].data->get_displacement() > max_disp){
				max_disp = test.bulk[i].data->get_displacement();
			}
		}
		
//		std::cout << std::endl;
		for(unsigned int i = 0; i < test.N; i++){
//			std::cout << "Calculating force on particle: " << i << std::endl;
			test.verlet_integrator.verlet_integration_velocity(test.bulk[i]);
			test.kinetic_energy(test.atoms[i]);
		}
		calc_temperature(test.get_kinetic_energy(), test.N);
		calc_pressure(test.verlet_integrator.get_p_int(), test.N, test.V);
		calc_specific_heat(test.get_kinetic_energy(), test.get_kinetic_energy_squared(), test.N);
//		cout << "T = " << T << endl << "P = " << P << endl;

		data[0] = t*timestep;
		data[1] = test.get_kinetic_energy();
		data[2] = test.verlet_integrator.e_pot;
		data[3] = test.get_kinetic_energy() + test.verlet_integrator.e_pot;
		data[4] = data[3]/test.N;
		data[5] = r_msd;
		data[6] = P;
		data[7] = T;
		data[8] = test.debye_temp(r_msd, 50, 1);
		data[9] = test.cohEnergy(test.N, (test.verlet_integrator.e_pot+0.5*test.get_kinetic_energy()));

//		std::cout << "Store data" << std::endl;
		writer.store_data(data);
		for(int i = 0; i < test.N; i++){
			writer.store_atom(*test.bulk[i].data);
		}
			
		if(max_disp > 0.5*cutoff){
			for(unsigned int i = 0; i < test.N; i++){
				test.bulk[i].clear_verlet_list();
			}
			max_disp = 0;
			test.update_verlet_lists();
		}
	}

	

	world w(2, 2, 2, 1, BCC);
//	std::cout << w.N << std::endl;
/*
	for(int i=0; i<(w.N); i++){
		std::cout << w.atoms[i].pos.x << "\t" << w.atoms[i].pos.y << "\t" << w.atoms[i].pos.z << "   (" << i+1 << ")" << std::endl;
	}

	writer.store_data(data);
*/
	int temp;
	std::cin >> temp;

	return 0;
}

void calc_temperature(float E_kin, int N) //Temperature
{
	T = E_kin / (3.0*kB*N);
//	cout << "E_kin = " << E_kin << endl << "kB = " << kB << endl << "N = " << N << endl;
}

void calc_pressure(float p_sum, int N, float V) //internal pressure
{
	P = N*kB*T/V + p_sum;
//	cout << "kB = " << kB << endl << "N = " << N << endl << "T = " << T << endl << "V = " << V << endl << "p_sum = " << p_sum << endl;
}

void calc_specific_heat(float E_kin, float E_kin_sqr, int N)
{
	C_v = 3*N*kB/(2-4*N*(E_kin_sqr - E_kin*E_kin)/(3*E_kin*E_kin));
//	cout << "C_v = " << C_v << endl;
}






//Thread test:
/*void *position(void* arg)
{
	world test = *(world *)arg;
	float max_disp = 0;
	for(unsigned int i = 0; i < test.N; i++){
		std::cout << "Old position of particle " << i << ": " << test.bulk[i].data->pos << std::endl;
		std::cout << "Old velocity of particle " << i << ": " << test.bulk[i].data->vel << std::endl;
		test.verlet_integrator.verlet_integration_position(test.bulk[i]);
		if(test.bulk[i].data->get_displacement() > max_disp){
			max_disp = test.bulk[i].data->get_displacement();
		}
		std::cout << "New position of particle " << i << ": " << test.bulk[i].data->pos << std::endl;
	}
	std::cout << std::endl;
	pthread_exit(NULL);

	return 0;
}

void *velocity(void* arg)
{
	world test = *(world *)arg;
	for(unsigned int i = 0; i < test.N; i++){
		test.verlet_integrator.verlet_integration_velocity(test.bulk[i]);
		std::cout << "New velocity of particle " << i << ": " << test.bulk[i].data->vel << std::endl;
	}
	pthread_exit(NULL);

	return 0;
}

	pthread_t thread[2];
	int rc;
	cout << "creating thread 1 \n";
	rc = pthread_create(&thread[0], NULL, position, (void *)&test);
	if (rc)
	{
		cout << "Error: Unable to create thread \n";
		exit(-1);
	}
	rc = pthread_create(&thread[1], NULL, velocity, (void *)&test);
	if (rc)
	{
		cout << "Error: Unable to create thread \n";
		exit(-1);
	}
	pthread_exit(NULL);


*/   

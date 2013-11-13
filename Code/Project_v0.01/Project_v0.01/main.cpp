#include "vector_lib.h"
#include "world.h"
#include "verlet_list.h"
#include <iostream>
//#include <cstdlib>
//#include <pthread.h>

using namespace std;

/* ************ Natural Constants ************ */
#define kB 8.6173324e-5 

/* ************ -Global Variables- ************ */
float x_tot; //Total length of the crystal
float y_tot;
float z_tot;
float P; //Internal Pressure
float T; //Temperature

/* ************ ----Functions---- ************ */
void calc_temperature(float kinetic_energy, int N);
void calc_pressure(float p_sum, int N, float V);

int main()
{
	world test(5);

	std::cout << "Total number of particles: " << test.N << std::endl;
	test.bulk[0].data->pos = vector_3d(1.0, 0.0, 0.0);
	test.bulk[1].data->pos = vector_3d(0.0, 1.0, 0.0);
	test.bulk[2].data->pos = vector_3d(0.0, 0.0, 1.0);
	test.bulk[3].data->pos = vector_3d(1.0, 0.0, 1.0);

	test.bulk[0].data->acc = vector_3d(25.0, 0.0, 1.0);
	test.bulk[1].data->vel = vector_3d(3.0, 0.0, 0.0);
	test.bulk[2].data->vel = vector_3d(1.0, 0.4, 1.2);
	test.bulk[3].data->vel = vector_3d(1.0, 1.0, 0.0);
	test.bulk[4].data->vel = vector_3d(0.1, 0.3, 0.3);

	x_tot = test.x_tot;
	y_tot = test.y_tot;
	z_tot = test.z_tot;

	test.update_verlet_lists();

	/* Move system to next time step */
	float max_disp = 0;
	test.verlet_integrator.reset_p_int();
	test.increase_kinetic_energy();
	for(unsigned int i = 0; i < test.N; i++){
//		std::cout << "Old position of particle " << i << ": " << test.bulk[i].data->pos << std::endl;
//		std::cout << "Old velocity of particle " << i << ": " << test.bulk[i].data->vel << std::endl;
		std::cout << "Updating position of particle " << i << " of " << test.N << " particles" << std::endl;
		test.verlet_integrator.verlet_integration_position(test.bulk[i]);
		if(test.bulk[i].data->get_displacement() > max_disp){
			max_disp = test.bulk[i].data->get_displacement();
		}
//		std::cout << "New position of particle " << i << ": " << test.bulk[i].data->pos << std::endl;
	}
	std::cout << std::endl;
	for(unsigned int i = 0; i < test.N; i++){
		std::cout << "Calculating force on particle: " << i << std::endl;
		test.verlet_integrator.verlet_integration_velocity(test.bulk[i]);
//		std::cout << "New velocity of particle " << i << ": " << test.bulk[i].data->vel << std::endl;
		test.increase_kinetic_energy(test.atoms[i]);
	}
	calc_temperature(test.get_kinetic_energy(), test.N);
	calc_pressure(test.verlet_integrator.get_p_int(), test.N, test.V);
	cout << "T = " << T << endl << "P = " << P << endl;

	for(unsigned int i = 0; i < test.N; i++){
		test.bulk[i].clear_verlet_list();
	}

/*
	world w(5, 5, 5, 1);
	
	std::cout << w.atoms[1].pos.x;
	
*/

	world w(3, 3, 3, 1);
	std::cout << w.N << std::endl;
	for(int i=0; i<w.N; i++){
		std::cout << w.atoms[i].pos.x << "\t" << w.atoms[i].pos.y << "\t" << w.atoms[i].pos.z << "   (" << i+1 << ")" << std::endl;
	}

	int temp;
	std::cin >> temp;

	return 0;
}

void calc_temperature(float kinetic_energy, int N) //Temperature
{
	T = kinetic_energy / (3.0*kB*N);
	cout << "E_kin = " << kinetic_energy << endl << "kB = " << kB << endl << "N = " << N << endl;
}

void calc_pressure(float p_sum, int N, float V) //internal pressure
{
	P = N*kB*T/V + p_sum;
	cout << "kB = " << kB << endl << "N = " << N << endl << "T = " << T << endl << "V = " << V << endl << "p_sum = " << p_sum << endl;
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

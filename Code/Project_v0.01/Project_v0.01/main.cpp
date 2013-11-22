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
	world test(3,3,3,0.1, 37199230118 ,20,BCC);

	x_tot = test.x_tot;
	y_tot = test.y_tot;
	z_tot = test.z_tot;

	verlet_list *current;
	test.update_verlet_lists();

	float data[10];

	float t_max = 20;
	float timestep = 0.0000002;
	float cutoff = 0.05;

	float max_disp = 0;

	test.integrate(t_max);

//	world w(2, 2, 2, 1, BCC);
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

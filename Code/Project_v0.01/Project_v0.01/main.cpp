#include "vector_lib.h"
#include "world.h"
#include "verlet_list.h"
#include <iostream>
using namespace std;

float x_tot; //Variable containing total length of the crystal;
float y_tot;
float z_tot;

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
	float r_msd = 0;
	float E_kin = 0;
	for(unsigned int i = 0; i < test.N; i++){
//		std::cout << "Old position of particle " << i << ": " << test.bulk[i].data->pos << std::endl;
//		std::cout << "Old velocity of particle " <<i << ": " << test.bulk[i].data->vel << std::endl;
		std::cout << "Updating position of particle " << i << " of " << test.N << " particles" << std::endl;
		test.verlet_integrator.verlet_integration_position(test.bulk[i]);
		
		
		//calculate the msd
		r_msd += test.msd(test.atoms[i], test.N);
		//calculate the kinetic energy
		E_kin += (test.atoms[i].mass*test.atoms[i].vel*test.atoms[i].vel)/2;
		
		
		//this below is working for the MSD
		/*
		*vector_3d r = test.atoms[i].pos.diff(test.atoms[i].orig_pos, x_tot, y_tot, z_tot);
		*msd += (r*r)/test.N;
		*/
		//Print the MSD to track that it's working
		std::cout << "------> MSD: " << r_msd << std::endl;
 
		
		if(test.bulk[i].data->get_displacement() > max_disp){
			max_disp = test.bulk[i].data->get_displacement();
		}

		
//		std::cout << "New position of particle " << i << ": " << test.bulk[i].data->pos << std::endl;
	}
	std::cout << "------> Debey Temp: " << test.debye_temp(r_msd, 50, 1) << std::endl;
	std::cout << "------> Energy tot: " <<  test.verlet_integrator.e_pot+E_kin << std::endl;
	std::cout << "------> CohEnergy: " <<  test.cohEnergy(test.N, (test.verlet_integrator.e_pot+E_kin)) << std::endl;
	
	std::cout << std::endl;
	for(unsigned int i = 0; i < test.N; i++){
		std::cout << "Calculating force on particle: " << i << std::endl;
		test.verlet_integrator.verlet_integration_velocity(test.bulk[i]);
//		std::cout << "New velocity of particle " << i << ": " << test.bulk[i].data->vel << std::endl;
	}

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

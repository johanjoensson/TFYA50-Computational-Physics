#include "vector_lib.h"
#include "world.h"
#include "verlet_list.h"
#include <iostream>

//Some global variables needed for testing. A better solution should be possible//
float x_tot;
float y_tot;
float z_tot;
float distance(vector_3d atom1_pos, vector_3d atom2_pos);

int main()
{
	world test(5);
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
	for(unsigned int i = 0; i < test.N; i++){
		test.verlet_integrator.verlet_integration_velocity(test.bulk[i]);
		std::cout << "New velocity of particle " << i << ": " << test.bulk[i].data->vel << std::endl;
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


float distance(vector_3d atom1_pos, vector_3d atom2_pos)
{
	if(abs(atom1_pos.x-atom2_pos.x) > 0.5*x_tot)
	{
		if(atom1_pos.x > atom2_pos.x)
			atom2_pos.x += x_tot;
		else
			atom2_pos.x -= x_tot;
	}
	if(abs(atom1_pos.y-atom2_pos.y) > 0.5*y_tot)
	{
		if(atom1_pos.y > atom2_pos.y)
			atom2_pos.y += y_tot;
		else
			atom2_pos.y -= y_tot;
	}	
	if(abs(atom1_pos.z-atom2_pos.z) > 0.5*z_tot)
	{
		if(atom1_pos.z > atom2_pos.z)
			atom2_pos.z += z_tot;
		else
			atom2_pos.z -= z_tot;
	}	
	vector_3d difference = atom1_pos-atom2_pos;
	float distance = difference*difference;
	return distance;
}
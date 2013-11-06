#include "world.h"
#include "verlet_list.h"
#include <iostream>


int main()
{
/*	world test(5);
	test.update_verlet_lists();

	for(int i = 0; i < test.N; i++){
		test.bulk[i].clear_verlet_list();
	}
*/	


	world w(5, 5, 5, 1);
	
	std::cout << w.atoms[1].pos.x;
	
	int temp;
	std::cin >> temp;

	return 0;
}
#include "world.h"
#include "verlet_list.h"
#include <iostream>

int main()
{
	world test(5);
	test.update_verlet_lists();

	for(int i = 0; i < test.N; i++){
		test.bulk[i].clear_verlet_list();
	}
	
	return 0;
}
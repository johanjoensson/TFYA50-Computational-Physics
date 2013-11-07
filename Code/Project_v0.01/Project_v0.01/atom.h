#ifndef ATOM_H
#define ATOM_H

#include "vector_lib.h"
#include <cmath>

class atom{
private:
	vector_3d next_acc;
	float displacement;
public:
	atom();
	atom(vector_3d position, vector_3d velocity, vector_3d acceleration);

	void set_next_acc(vector_3d new_acc);
	void incr_next_acc(vector_3d new_acc);
	void decr_next_acc(vector_3d new_acc);

	void incr_displacement(float r);
	void zero_displacement();
	float get_displacement();
	//float distance(vector_3d atom2_pos); Function temporarily placed in main.cpp, problem obtaining the x,y,z_tot variables from world, since world already includes atom

	vector_3d get_next_acc();

	void update_acceleration();

	vector_3d pos;
	vector_3d vel;
	vector_3d acc;
	float mass;

	//float x_tot;
	//float y_tot;
	//float z_tot;
};

#endif /* ATOM_H */

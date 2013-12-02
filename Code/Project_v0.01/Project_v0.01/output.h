#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "atom.h"

class outputter{
private:
	std::ofstream file;
	std::ofstream visualisation_file;
	std::ofstream back2back_file;

	std::ostringstream temp;
public:
	~outputter();
	outputter();
	outputter(char* filename);
	outputter(char* filename, char* vis_name);
	void store_data(float data[8]);
	void store_atom(atom a);
	void store_back2back(float mass, float epsi, float sigma, float x_dim, float y_dim, float z_dim, int N, float cutoff, float collision_rate, atom* a);
	void timestep_end();
	void init_data_file();
	void close_files();
};
#endif /* OUTPUT_H */

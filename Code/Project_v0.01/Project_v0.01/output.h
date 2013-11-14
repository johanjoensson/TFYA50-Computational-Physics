#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <fstream>

#include "atom.h"

class outputter{
private:
	std::ofstream file;
	std::ofstream visualisation_file;
public:
	outputter(char* filename);
	outputter(char* filename, char* vis_name);
	void store_data(float data[8]);
	void store_atom(atom a);
	void init_data_file();
};
#endif /* OUTPUT_H */

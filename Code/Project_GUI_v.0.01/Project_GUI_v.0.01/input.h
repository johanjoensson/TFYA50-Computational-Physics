#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>

#include "vector_lib.h"
#include "world.h"

struct Material{
	std::string name;
	float mass;
	float a;
	float sigma;
	float epsilon;
};

class inputter{
private:
	std::ifstream file;
	std::ifstream back2back_file;


public:
	~inputter();
	inputter(char* file_name);
	inputter();
	void close_file();
	void close_b2b();

	unsigned int num_mat;

	Material* get_material(char* text_file);

	world* get_equi_data(std::string str);
	
};

#endif /* INPUT_H */
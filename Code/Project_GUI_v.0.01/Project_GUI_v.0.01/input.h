#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <fstream>

#include "vector_lib.h"

struct Material{
	std::string name;
	float mass;
	float sigma;
	float epsilon;
};

class inputter{
private:
	std::ifstream file;

public:
	inputter(char* file_name);

	void get_data();
	
};

#endif /* INPUT_H */
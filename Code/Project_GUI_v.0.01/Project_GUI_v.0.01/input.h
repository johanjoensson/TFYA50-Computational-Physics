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
}Material_t;

class inputter{
private:
	std::ifstream file;

public:
	
};

#endif /* INPUT_H */
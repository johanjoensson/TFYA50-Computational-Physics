#ifndef ATOM_H
#define ATOM_H

#include "vector_lib.h"

class atom{
public:
	atom();
	atom(vector_3d position, vector_3d velocity, vector_3d acceleration);

	vector_3d pos;
	vector_3d vel;
	vector_3d acc;
};

#endif /* ATOM_H */
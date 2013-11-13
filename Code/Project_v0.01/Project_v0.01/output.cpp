#include "output.h"

outputter::outputter(char* filename)
{
	file.open(filename, std::ios::out|std::ios::trunc);
}

/* if we need to store 5 properties, change to match our needs */
void outputter::store_data(float data[8])
{
	for(int	i = 0; i < 8; i++){
		file << data[i] << "\t";
	}
	file << std::endl;
	return;
}

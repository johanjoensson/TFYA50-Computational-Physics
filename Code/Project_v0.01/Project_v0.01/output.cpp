#include "output.h"

outputter::outputter(char* filename)
{
	file.open(filename, std::ios::out|std::ios::trunc);

	file << "Time" << "\t" << "Kinetic Energy" << "\t" << "Potential Energy" << "\t" << "Total Energy" << "\t" << "MSD" << "\t" << "Temperature" << "\t" << "Internal Pressure"<< "\t" << "Debeye Temperature"<< "\t" << std::endl;

}

/* if we need to store 5 properties, change to match our needs */
void outputter::store_data(float data[8])
{
	for(int	i = 0; i < 8; i++){
		if(i > 0){
			file << "\t";
		}
		file << data[i];
	}
	file << std::endl;
	return;
}

#include "output.h"

outputter::outputter(char* filename)
{
	file.open(filename, std::ios::out|std::ios::trunc);

	file << "Time" << "\t" << "Maximum displacement" << "\t" << "MSD" << "\t" << "Kinetic energy" << "\t" << "Data index 4" << "\t" << "Data index 5" << "\t" << "Data index 6"<< "\t" << "Data index 7"<< "\t" << std::endl;

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

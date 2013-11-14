#include "output.h"

void outputter::init_data_file()
{
	file << "Time" << "\t";
	file << "Kinetic Energy" << "\t";
	file << "Potential Energy" << "\t";
	file << "Total Energy" << "\t";
	file << "Cohesive Energy" << "\t";
	file << "MSD" << "\t";
	file << "Internal Pressure" << "\t";
	file << "Temperature" << "\t";
	file << "Debeye Temperature" << "\t";
	file << "Specific Heat" << "\t";

}

outputter::outputter(char* filename)
{
	file.open(filename, std::ios::out|std::ios::trunc);

	file << "Time" << "\t" << "Kinetic Energy" << "\t" << "Potential Energy" << "\t" << "Total Energy" << "\t" << "MSD" << "\t" << "Temperature" << "\t" << "Internal Pressure"<< "\t" << "Debeye Temperature"<< "\t" << std::endl;

}

outputter::outputter(char* filename, char* vis_name)
{
	file.open(filename, std::ios::out|std::ios::trunc);
	visualisation_file.open(vis_name, std::ios::out|std::ios::trunc);
}

void outputter::store_data(float data[10])
{
	for(int	i = 0; i < 10; i++){
		if(i != 0){
			file << "\t" << data[i];
		}else{
			file << data[i];
		}
	}
	file << std::endl;
	return;
}

void outputter::store_atom(atom a)
{
	visualisation_file << a.pos;	
}

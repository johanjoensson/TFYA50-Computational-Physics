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
	file << "Specific Heat" << std::endl;

}

outputter::~outputter()
{
	file.close();
	visualisation_file.close();
}

outputter::outputter()
{
	file.open("toto.txt");
	visualisation_file.open("titi.txt", std::ios::out|std::ios::trunc);
	init_data_file();
}

outputter::outputter(char* filename)
{
	file.open(filename, std::ios::out|std::ios::trunc);
	init_data_file();
}

outputter::outputter(char* filename, char* vis_name)
{
	file.open(filename, std::ios::out|std::ios::trunc);
	init_data_file();
	visualisation_file.open(vis_name, std::ios::out|std::ios::trunc);
}

void outputter::store_data(float data[10])
{
	for(int	i = 0; i < 10; i++){
		if(i == 0){
			file << data[i];
		}else{
			file << "\t" << data[i];
		}
	}
	file << std::endl;
	file.flush();
	return;
}

void outputter::store_atom(atom a)
{
	visualisation_file << a.pos;
	visualisation_file.flush();
}

void outputter::close_files()
{
	file.close();
	visualisation_file.close();
}
#include "output.h"

void outputter::init_data_file()
{
	file.open("toto.txt", std::ios::trunc);
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
	file.close();

	visualisation_file.open("titi.txt", std::ios::trunc);
	visualisation_file.close();
}

outputter::~outputter()
{
	file.close();
	visualisation_file.close();
	back2back_file.close();
}

outputter::outputter()
{
//	file.open("toto.txt");
//	visualisation_file.open("titi.txt", std::ios::out|std::ios::trunc);
//	back2back_file.open("back2back.txt", std::ios::out|std::ios::trunc);
//	init_data_file();
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
	file.open("toto.txt", std::ios::out|std::ios::app);
	for(int	i = 0; i < 10; i++){
		if(i == 0){
			file << data[i];
		}else{
			file << "\t" << data[i];
		}
	}
	file << std::endl;
	file.flush();

	file.close();
	return;
}

void outputter::store_atom(atom a)
{
//	visualisation_file << a.pos;
//	visualisation_file.flush();
	temp << a.pos;
}

void outputter::store_back2back(float mass, float epsi, float sigma, float x_dim, float y_dim, float z_dim, int per_x, int per_y, int per_z, int N, float cutoff, float collision_rate, float temp, atom* a)
{
	back2back_file.open("back2back.txt", std::ios::out|std::ios::trunc);
	back2back_file << mass << " " << epsi << " " << sigma << " " << x_dim << " " << y_dim << " " << z_dim << " " << per_x << " " << per_y << " " << per_z << " " << N << " " << cutoff << " " << collision_rate << " " << temp << " ";
	for(int	i = 0; i < N; i++){
			back2back_file << a[i].orig_pos << a[i].pos << a[i].vel;
	}
	back2back_file.flush();

	back2back_file.close();
	return;
}

void outputter::timestep_end()
{
	visualisation_file.open("titi.txt", std::ios::out|std::ios::app);
	visualisation_file << temp.str() << std::endl;
//	visualisation_file << std::endl;
	visualisation_file.flush();
	temp.clear();
	temp.str("");

	visualisation_file.close();
}

void outputter::close_files()
{
	file.close();
	visualisation_file.close();
	back2back_file.close();
}
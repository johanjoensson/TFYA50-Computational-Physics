#include "input.h"

#include <string>

inputter::~inputter()
{
	file.close();
	back2back_file.close();
}

void inputter::close_file()
{
	file.close();
	back2back_file.close();
}
inputter::inputter(char* file_name)
{
	file.open(file_name, std::ios::in);
	back2back_file.open("back2back.txt");
}

void extract_mat_param(Material &mat, std::string data, unsigned int j)
{
	switch(j){
	case 0:
		mat.name = data;
		break;
	case 1:
		mat.mass = atof(data.c_str());
		break;
	case 2:
		mat.a = atof(data.c_str());
		break;
	case 3:
		mat.epsilon = atof(data.c_str());
		break;
	case 4:
		mat.sigma = atof(data.c_str());
		break;
	default:
		break;
	}
}
/*
int inputter::num_materials()
{
	unsigned int l = 0;
	while(!file.eof()){
		getline(file, str);
		l++;
	}

	return l-1;
}
*/

Material* inputter::get_material(char* text_file)
{
	std::ofstream output("test.txt", std::ios::out|std::ios::trunc);
	std::string str;
	std::string delim = "\t";
	std::string token;

	unsigned int l = 0;
	while(!file.eof()){
		getline(file, str);
		l++;
	}

	num_mat = l - 1;
	output << "Number of lines" << l << std::endl;
	file.clear();
	file.seekg(0, file.beg);
	Material* res = new Material[l];
	std::getline(file,str);

	unsigned int i = 0;
	unsigned int j = 0;
	size_t pos = 0;
	while(!file.eof()){
		std::getline(file,str);
		i = 0;
		while((pos = str.find(delim)) != std::string::npos){
			token = str.substr(0, pos);
			str.erase(0, pos + delim.length());
			extract_mat_param(res[j], token, i);
			output << token << " " ;

			i++;
		}
		token = str;
		extract_mat_param(res[j], token, i);
		output << token << " " ;
		output << std::endl;

		j++;
	}
	return res;
}

/*
world* inputter::get_equi_data()
{
	if( back2back_file.is_open())
	{
		float mass, epsi, sigma, x_dim, y_dim, z_dim, N, cutoff, collision_rate;
		float a, b, c, d, e, f;

		back2back_file >> mass >> epsi >> x_dim >> y_dim >> z_dim >> N >> cutoff >> collision_rate;  
		for(int i = 0; i < N; i++){
			back2back_file >> a >> b >> c;
			atoms[i].pos= vector_3d(a,b,c);
			back2back_file >> d >> e >> f;
			atoms[i].vel= vector_3d(d,e,f);

		}

		back2back_file.close();
	}
	else
		std::cout << "Impossible to open the file!" << std::endl;


	world *res = new world;

	return res;
}
*/
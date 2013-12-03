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
//	back2back_file.close();
}
void inputter::close_b2b()
{
	back2back_file.close();
}

inputter::inputter(char* file_name)
{
	file.open(file_name, std::ios::in);
//	back2back_file.open("back2back.txt");
}
inputter::inputter()
{
//	back2back_file.open("back2back.txt");
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
	std::string str;
	std::string delim = "\t";
	std::string token;

	unsigned int l = 0;
	while(!file.eof()){
		getline(file, str);
		l++;
	}

	num_mat = l - 1;
	file.clear();
	file.seekg(0, file.beg);
	Material* res = new Material[l+1];
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

			i++;
		}
		token = str;
		extract_mat_param(res[j], token, i);

		j++;
	}
	return res;
}

world* inputter::get_equi_data(std::string str)
{
	world *res;
	PBC conditions;
	back2back_file.open(str, std::ios::in);
	if( back2back_file.is_open())
	{
		std::string tmp;
		unsigned int N, per_x, per_y, per_z;
		float mass, epsi, sigma, x_dim, y_dim, z_dim, cutoff, collision_rate, temp;
		float a, b, c, d, e, f, g, h, j;

		back2back_file >> mass >> epsi >> sigma >> x_dim >> y_dim >> z_dim >> per_x >> per_y >> per_z >> N >> cutoff >> collision_rate >> temp;  
		res = new world(N, x_dim, y_dim, z_dim, temp);

		for(int i = 0; i < N; i++){
			back2back_file >> tmp >> a >> tmp >> b >> tmp >> c;
			back2back_file >> tmp >> d >> tmp >> e >> tmp >> f;
			back2back_file >> tmp >> g >> tmp >> h >> tmp >> j;
			res->atoms[i] = atom(vector_3d(a,b,c),vector_3d(d,e,f), vector_3d(g,h,j));
			res->atoms[i].mass = mass;
		}

		back2back_file.close();

		if(per_x != 0){
			conditions.x = true;
		}else{
			conditions.x = false;
		}
		if(per_y != 0){
			conditions.y = true;
		}else{
			conditions.y = false;
		}
		if(per_z != 0){
			conditions.z = true;
		}else{
			conditions.z = false;
		}
		res->set_epsilon(epsi);
		res->set_sigma(sigma);
		res->set_cutoff(cutoff);
		
		if(collision_rate != 0){
			res->set_thermostat(true);
			res->set_collision_rate(collision_rate);
		}else{
			res->set_thermostat(false);
		}

		res->set_boundary(conditions);
	}

	return res;
}
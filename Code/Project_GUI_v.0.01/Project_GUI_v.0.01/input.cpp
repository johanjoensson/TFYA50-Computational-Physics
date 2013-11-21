#include "input.h"

inputter::inputter(char* file_name)
{
	file.open(file_name, std::ios::in);
}

void inputter::get_data()
{
	std::ofstream output("test.txt", std::ios::out|std::ios::trunc);
	float f[10];
	while(!file.eof()){
		file >> f[0] >> f[1] >> f[2] >> f[3] >> f[4] >> f[5] >> f[6] >> f[7] >> f[8] >> f[9];
		for(int i = 0; i < 10; i++){
			output << f[i] << " ";
		}
		output << std::endl;
	}
}
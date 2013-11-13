#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <fstream>

class outputter{
private:
	std::ofstream file;
public:
	outputter(char* filename);
	void store_data(float data[8]);
};
#endif /* OUTPUT_H */

#include "average.h"
#include <iostream>


float regularAverage(int startTime, int endTime){
	float sum=0;
	for(int i=startTime;i<=(endTime-startTime);i++){
		sum+=value[i]; //Fetch value at time [i] from saved values
	}
	sum = sum/endTime;
	return sum;
}

float averageValue(int startTime, int endTime, type_of_average){
	float average;
	switch(type_of_average){
		case KINETIC_ENERGY: case POTENTIAL_ENERGY: case TEMPERATURE:
			regularAverage(int startTime); break;
		case MSD:
			msdAverage(int startTime, int endTime); break;
	}
	default:
		std::cout << "Bad type of averge" << std::endl; average=0; break;	
	return average;
} 	
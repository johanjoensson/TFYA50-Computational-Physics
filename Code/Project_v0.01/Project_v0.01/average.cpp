#include "average.h"
#include <iostream>
#include <fstream>
#include <string>

float* averageValue(int startTime, int endTime){
	char line[256];
	float average[10];
	float tmp_avg[10];
	int dt = endTime-startTime;
	
	std::ifstream input("toto.txt");
	input.seekg(0, input.beg);	
	
	float E_kin,E_pot,E_tot,E_coh,MSD,int_p,temp,deb,Spec_heat,diff_const;
	//float tmp_E_kin, tmp_E_pot, tmp_E_tot, tmp_E_coh, tmp_MSD, tmp_int_p, tmp_temp, tmp_deb, tmp_Spec_heat;
	E_kin=E_pot=E_tot=E_coh=MSD=int_p=temp=deb=Spec_heat=diff_const=0;
	
	
	if (input.is_open()){
		int i = 0;
		while(startTime<i){
			input.getline(line, 256);
			i++;
		}
		
		for(int k=i;k<=endTime;k++){
			
			input.getline(line, 256);
			std::string delim = "\t";
			size_t pos = 0;
			unsigned int j = 0;
			
			while((pos = input.find(delim)) != std::string::npos){
				token = line.substr(0, pos);
				line.erase(0, pos + delim.length());
				tmp_avg[j] = atof(token.c_str());
				j++;
			}
			
			E_kin += tmp_avg[1];
			E_pot += tmp_avg[2];
			E_tot += tmp_avg[3];
			E_coh += tmp_avg[4];
			MSD += tmp_avg[5];
			int_p += tmp_avg[6];
			temp += tmp_avg[7];
			deb += tmp_avg[8];
			Spec_heat += tmp_avg[9];
		}
	}
	
	average[0] = E_kin/dt;
	average[1] = E_pot/dt;
	average[2] = E_tot/dt;
	average[3] = E_coh/dt;
	average[4] = MSD/dt;
	average[5] = int_p/dt;
	average[6] = temp/dt;
	average[7] = deb/dt;
	average[8] = Spec_heat/dt;
	average[9] = MSD/(3*dt); //diffusan konstant
	
	
	return average;
}

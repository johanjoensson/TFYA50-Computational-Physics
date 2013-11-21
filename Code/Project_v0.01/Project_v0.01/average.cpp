#include "average.h"
#include <iostream>
#include <fstream>

float* averageValue(int startTime, int endTime){
	char line[256];
	float average[10];
	int dt = endTime-startTime;
	std::ifstream input("toto.txt");
	input.seekg(0, input.beg);	
	float E_kin,E_pot,E_tot,E_coh,MSD,int_p,temp,deb,Spec_heat,diff_const;
	float tmp_E_kin, tmp_E_pot, tmp_E_tot, tmp_E_coh, tmp_MSD, tmp_int_p, tmp_temp, tmp_deb, tmp_Spec_heat;
	E_kin=E_pot=E_tot=E_coh=MSD=int_p=temp=deb=Spec_heat=diff_const=0;	
	if (input.is_open()){
		int i = 0;
		while(startTime<i){
			input.getline(line, 256);
			i++;
		}
		for(i<=endTime;i++){
			input.getline(line, 256);
			line >> tmp_E_kin >> tmp_E_pot >> tmp_E_tot >> tmp_E_coh >> tmp_int_p >> tmp_temp >> tmp_deb >> tmp_Spec_heat;
			E_kin += tmp_E_kin;
			E_pot += tmp_E_pot;
			E_tot += tmp_E_tot;
			E_coh += tmp_E_coh;
			int_p += tmp_int_p;
			temp += tmp_temp;
			deb += tmp_deb;
			Spec_heat += tmp_Spec_heat;
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
	average[9] = diff_const/(2*dt);
	
	
	return average;
}

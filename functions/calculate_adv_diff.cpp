#include <admodel.h>
using namespace std;
void calculate_adv_diff(dvar_vector& ratio_adv_diff, dvar_vector& diffz, dvar_vector& ratio_adv_diff2, dvar_vector ADVz, dvar_vector DIFFz, double len, double DzPHY){
	for(int g(1);g<=3;g++){
        	ratio_adv_diff[g] = (ADVz[g] / DIFFz[g])/ len;
       		diffz[g] = DIFFz[g] * len * len;
       		ratio_adv_diff2[g] = (ADVz[g] * len * (diffz[g] + DzPHY)) / (diffz[g] * diffz[g]);
      	}

}

#include <admodel.h>
using namespace std;
void calculate_adv_diff_bis(dvar_matrix& ratio_adv_diff, dvar_matrix& diffz, dvar_matrix& ratio_adv_diff2, dvar_matrix& eyesurf, dvar_vector ADVz, dvar_vector DIFFz, double DzPHY,dvector L, dvar_vector EYE_DIAM_ALLOM ){
	 
	for(int l(1);l<=L.size();l++){
		double len = L[l];
		for(int g(1);g<=3;g++){
        		ratio_adv_diff[g][l] = (ADVz[g] / DIFFz[g])/ len;
       			diffz[g][l] = DIFFz[g] * square(len);
       			ratio_adv_diff2[g][l] = (ADVz[g] * len * (diffz[g][l] + DzPHY)) / square(diffz[g][l]);
		 	eyesurf[g][l]=pow(len, 2.*EYE_DIAM_ALLOM[g]);
		}
      	}

}

#include <admodel.h>

using namespace std;

void calculate_profile(dvar3_array& profile, dvar_matrix& profiletot, dvar3_array habitat_env, dvar_vector ratio_adv_diff2, dvar_vector diffz, dvar_vector ratio_adv_diff, double DzPHY, int bottom){


	for(int dn(1);dn<=2;dn++){
   	  for(int g(1);g<=3;g++){
          	profiletot[dn][g] = 0.; //initialiser
        	for(int z(1);z<=bottom;z++){
           		 profile[dn][g][z]=exp(ratio_adv_diff2[g]*log((habitat_env[dn][g][z]*diffz[g]+DzPHY) / (habitat_env[dn][g][1] * diffz[g] + DzPHY)) - ratio_adv_diff[g] * (habitat_env[dn][g][z] - habitat_env[dn][g][1]));
                        
          		 profiletot[dn][g] +=profile[dn][g][z] ;
       		 } //end of z loop

    	 } //end of g loop
 	} //end of dn loop

}


#include <admodel.h>

using namespace std;

void update_habitat_env(dvar4_array& habitat_env, dvariable profile_prey, dvar_matrix selectiv,dvar4_array& profile, dvar3_array& profiletot, dvar_matrix ratio_adv_diff2, dvar_matrix diffz, dvar_matrix ratio_adv_diff, double DzPHY, dvariable c, int dn, int g, int s, int z, size_t L_size){
	dvariable P = 0.;
	//dvar_vector tt = column(selectiv,s);
	for(int i(1);i<= L_size;i++){
		P += profile_prey * selectiv[s][i];
	}
	
	habitat_env[dn][g][z] *= P/(c + P);
	profile[dn][g][z][s]=exp(ratio_adv_diff2[g][s]*log((habitat_env[dn][g][z][s]*diffz[g][s]+DzPHY) / (habitat_env[dn][g][1][s] * diffz[g][s] + DzPHY)) - ratio_adv_diff[g][s] * (habitat_env[dn][g][z][s] - habitat_env[dn][g][1][s]));
        profiletot[dn][g][s] +=profile[dn][g][z][s] ;


}

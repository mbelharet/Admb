#include <admodel.h>
using namespace std;
void calculate_habitat_env(dvar4_array& habitat_env, dvar4_array light_pref, dvar_vector temper_pref, dvar_matrix oxy_pref, dvar4_array& profile, dvar3_array& profiletot, dvar_matrix ratio_adv_diff2, dvar_matrix diffz, dvar_matrix ratio_adv_diff, double DzPHY, int dn, int g, int z, int s ){




					habitat_env[1][1][z][s] = light_pref[1][1][z][s] * temper_pref[z] * oxy_pref[1][z];
					habitat_env[2][1][z][s] = habitat_env[1][1][z][s];
                                	habitat_env[dn][2][z][s] = light_pref[dn][2][z][s] * oxy_pref[2][z];
                                	habitat_env[dn][3][z][s] = light_pref[1][3][z][s] * oxy_pref[3][z];
					habitat_env[dn][4][z][s] = light_pref[1][4][z][s] * oxy_pref[4][z];

				
					 profile[dn][g][z][s]=exp(ratio_adv_diff2[g][s]*log((habitat_env[dn][g][z][s]*diffz[g][s]+DzPHY) / (habitat_env[dn][g][1][s] * diffz[g][s] + DzPHY)) - ratio_adv_diff[g][s] * (habitat_env[dn][g][z][s] - habitat_env[dn][g][1][s])); 
				 	profiletot[dn][g][s] +=profile[dn][g][z][s] ;


}


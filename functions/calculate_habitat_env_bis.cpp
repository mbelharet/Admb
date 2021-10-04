#include <admodel.h>
using namespace std;
void calculate_habitat_env_bis(dvar3_array& habitat_env, dvar3_array light_pref, dvar_vector temper_pref, dvar_matrix oxy_pref, dvar3_array& profile, dvar_matrix& profiletot, dvar_matrix ratio_adv_diff2, dvar_matrix diffz, dvar_matrix ratio_adv_diff, double DzPHY, dvariable c1, dvariable c2, dvar_matrix& f_food, dvar4_array& profile_norm, dvector profile_size_1, dvar_vector light_pref_1, int s, dvar_vector& light2){

	size_t bottom = temper_pref.size();
	dvar_vector profile_1(1,bottom);
	dvar_vector profile_norm_1(1,bottom);
	dvariable profiletot_1;
	dvar_vector habitat_env_1(1,bottom);


		for(int dn(1); dn<=2; dn++){
			profiletot[dn][1] = 0 ;
			profiletot[dn][2] = 0 ;
			profiletot[dn][3] = 0 ;


			for(int z(1); z<=bottom; z++){

					//f_food[1][z] = profile_size_1[z]/(c1 +  profile_size_1[z] );
					habitat_env[dn][1][z] = light_pref[1][1][z] * temper_pref[z];// * oxy_pref[1][z];
                                	habitat_env[dn][2][z] = light_pref[dn][2][z] * oxy_pref[2][z];
					//habitat_env[2][2][z] = f_food[1][z];
                                	habitat_env[dn][3][z] = light_pref[2][3][z]; //1; //  * oxy_pref[3][z];
					//habitat_env[2][3][z] = light_pref[2][3][z];

					

				for(int g=1;g<=3;g++){

				
					 profile[dn][g][z]=exp(ratio_adv_diff2[g][s]*log((habitat_env[dn][g][z]*diffz[g][s]+DzPHY) / (habitat_env[dn][g][1] * diffz[g][s] + DzPHY)) - ratio_adv_diff[g][s] * (habitat_env[dn][g][z] - habitat_env[dn][g][1])); 
				 	profiletot[dn][g] +=profile[dn][g][z] ;

					if(g==2 && dn==1){
						habitat_env_1[z] = light_pref_1[z]* oxy_pref[2][z];
						profile_1[z] = exp(ratio_adv_diff2[g][1]*log((habitat_env_1[z]*diffz[g][1]+DzPHY) / (habitat_env_1[1] * diffz[g][1] + DzPHY)) - ratio_adv_diff[g][1] * (habitat_env_1[z] - habitat_env_1[1]));
						profiletot_1 +=profile_1[z];

					}


				}
			}
		}
				 
				// profile total
				for(int z = 1; z <= bottom; z++){
					profile_norm_1[z] = profile_1[z]/profiletot_1;
					//light2[z] = profile_norm_1[z];
					for(int g(1); g<=3; g++){
						for(int dn(1); dn<=2; dn++){
							profile_norm[dn][g][z] = profile[dn][g][z] / profiletot[dn][g];
						}
					}
				}
				
				
				 // Les exceptions
				profiletot[2][2] = 0.;
                                profiletot[1][3] = 0.;

				for(int z = 1; z <= bottom; z++){

					f_food[1][z] = profile_norm[2][1][z]/(c1 +  profile_norm[2][1][z] );
                        		habitat_env[2][2][z] *= f_food[1][z];
					profile[2][2][z]=exp(ratio_adv_diff2[2][s]*log((habitat_env[2][2][z]*diffz[2][s]+DzPHY) / (habitat_env[2][2][1] * diffz[2][s] + DzPHY)) - ratio_adv_diff[2][s] * (habitat_env[2][2][z] - habitat_env[2][2][1]));
					profiletot[2][2] += profile[2][2][z];


					f_food[2][z] = profile_norm[1][2][z]/(c2 +  profile_norm[1][2][z] ); //profile_norm_1[z]/ (c2 +profile_norm_1[z]);// 

					habitat_env[1][3][z] *= f_food[2][z] ; // le jour dépend uniquement de la nourriture
					profile[1][3][z]=exp(ratio_adv_diff2[3][s]*log((habitat_env[1][3][z]*diffz[3][s]+DzPHY) / (habitat_env[1][3][1] * diffz[3][s] + DzPHY)) - ratio_adv_diff[3][s]* (habitat_env[1][3][z] - habitat_env[1][3][1]));
					profiletot[1][3] += profile[1][3][z];
				} 
				
				double alpha2 = max(0.0,1.0 - alpha1 - alpha3);

				for(int z = 1; z <= bottom; ++z){
					profile_norm[2][2][z][s] = profile[2][2][z] / profiletot[2][2];
					profile_norm[1][3][z][s] = profile[1][3][z] / profiletot[1][3];

					/*for(int dn(1); dn<=2; dn++){
						profile_g_comb[dn][z] = alpha1 * profile_norm[dn][1][z] + alpha2 * profile_norm[dn][2][z] + alpha3 * profile_norm[dn][3][z];
					}*/
				}



}

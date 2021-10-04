#include <admodel.h>

using namespace std;

void calculate_residuals(dvar_matrix& resid, dvar_vector sA_d, dvar_vector sA_n, dvar_matrix profile_g_comb, int bottom){
	for(int z=1; z<=bottom;z++){
   	 //for(int dn=1;dn<=2;dn++){
      		// resid[dn][z] = (acous[dn][z] - profile_g_comb[dn][z]) ;
   	 //}
	 	resid[1][z] = (sA_d[z] - profile_g_comb[1][z]) ;
		resid[2][z] = (sA_n[z] - profile_g_comb[2][z]) ;
	}
}

#include <admodel.h>

using namespace std;


void calculate_normalized_profile(dvar4_array& profile_norm, dvar4_array profile, dvar3_array profiletot, int dn, int g, int s, int bottom ){
	
	for(int z_(1);z_<=bottom;z_++){
		profile_norm[dn][g][z_][s] = profile[dn][g][z_][s] / profiletot[dn][g][s];
	}


}

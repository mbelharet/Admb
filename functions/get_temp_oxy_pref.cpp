#include <admodel.h>
#include <algorithm> 

void get_temp_oxy_pref(dvar_vector& temper_pref, dvar_matrix& oxy_pref,dvariable temper_1,dvariable temper_z, dvariable oxy_z, dvariable Ta, double Tref, dvariable SIGM_TCOR0, dvar_vector OXYRESP, dvar_vector OXYLIM, int z ){


		dvariable Tcor0 = exp(Ta / Tref - Ta / (temper_1 + 273.15));

 			 //Preference for temperature
     			dvariable Tcor = exp(Ta / Tref - Ta / (temper_z + 273.15));
     			temper_pref[z] = exp(-.5 * ((Tcor / Tcor0 - 1.) / SIGM_TCOR0)*((Tcor / Tcor0 - 1.) / SIGM_TCOR0));
			//temper_pref[2][z] = 1.;
			//temper_pref[3][z] = exp(-.5 * ((Tcor / Tcor0 - 1.) / SIGM_TCOR03)*((Tcor / Tcor0 - 1.) / SIGM_TCOR03));

			oxy_pref[1][z] = 1;
			oxy_pref[3][z] = 1; //1. / (1. + exp(OXYRESP[2] * (OXYLIM[2] - oxy_z)));
			oxy_pref[4][z] = 1;
			oxy_pref[2][z] = 1. / (1. + exp(OXYRESP[1] * (OXYLIM[1] - oxy_z)));




} // end of function

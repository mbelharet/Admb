#include <admodel.h>
using namespace std;

void get_light_pref(dvar4_array& light_pref, dvar_vector light, dvar_vector SIGM_LIGHT, dvar_vector OPT_LIGHT, dvariable d_len, dvar_vector nfactor, double EPS, dvariable eyesurf, dvariable oxy_m, dvariable ko2_max, dvariable a_o2, size_t dn, size_t g, size_t z, size_t s){ 
         
	dvariable var;
        dvariable mu ;
        dvariable sigm ;
        dvariable ssigm ;
        dvariable mode ;
	dvariable tmplight;

			dvariable light_z = light[z];

			/*if(z>=21){
				dvariable k = log(light[z-1]/light[z]);
				dvariable ko2 = ko2_max * exp(-a_o2*oxy_m);//max(c,lambda);//ko2_max * lambda;
				light_z = light[z-1]* exp(-k - ko2) ;
			
			}*/

			tmplight = (light_z / d_len) *eyesurf * nfactor[dn] + EPS;
			var = log(1. + square(SIGM_LIGHT[g]) / square(OPT_LIGHT[g]));
                        mu = log(OPT_LIGHT[g]) - .5 * var;

                  	sigm = sqrt(var);
                  	mode = exp(mu - var);
                	light_pref[dn][g][z][s] = (mode / tmplight) * exp((square(log(mode) - mu) - square(log(tmplight) - mu)) / (2. * var));

				

}

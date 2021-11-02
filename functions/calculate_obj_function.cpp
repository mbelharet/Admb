#include <admodel.h>

using namespace std;

dvariable calculate_obj_function(dvar_vector sA_d, dvar_vector sA_n, dvar3_array profile_g_comb, int bottom, double alpha1, double alpha3, dvariable p){
        dvariable f(0.);
	//dvariable f1(0.);
	//dvariable f2(0.);
	dvariable pr_mod_d;
	dvariable pr_mod_n;
	double alpha2 = max(0.0, 1 - alpha1 - alpha3);

		for(int z(1);z<=bottom;z++ ){
			pr_mod_d = alpha1 * profile_g_comb[1][1][z] + alpha2 * profile_g_comb[1][2][z] + p * alpha3 * profile_g_comb[1][3][z] + (1.-p) * alpha3 * profile_g_comb[1][4][z];
			pr_mod_n = alpha1 * profile_g_comb[2][1][z] + alpha2 * profile_g_comb[2][2][z] + p * alpha3 * profile_g_comb[2][3][z] + (1.-p) * alpha3 * profile_g_comb[2][4][z];

			dvariable w1 = sA_d[z]/max(sA_d);
			dvariable w2 = sA_n[z]/max(sA_n);

			double param = 1.;//a1e5;

			if(z>=21)
			{
				f +=  square( w1 * (param * sA_d[z]  - param*pr_mod_d) );
			}
	      		f +=  square(w2 * (param*sA_n[z]  - param*pr_mod_n) );
			
			//f +=  square( param * sA_d[z]  - param *pr_mod_d) ;
			//f +=  square(param * sA_n[z]  - param * pr_mod_n);


		}

		/*J[1][id] = f1 * 1e-5;
		J[2][id] = f2 * 1e-5;*/
		
		//dvariable f = f1 + f2;

   return f;
}

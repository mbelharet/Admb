#include <admodel.h>

void calculate_selectivity(dmatrix& selectiv, dvector L, dvector L_prey, double a1, double a2, double rho1, double rho2, double gamma){

	
	for(int i=1;i<=L.size();i++){
		double ss(0);
		for(int j=1;j<=L_prey.size();j++){

			double f = 1/(1 + exp(a1*(rho1 - L(i)/L_prey(j))));
			double g = 1 - 1/(1 + exp(a2*(rho2 - L(i)/L_prey(j))));

			selectiv[i][j] = f * g;
			ss += selectiv[i][j];
		}

		if(ss == 0){
			selectiv[i][i] = 1;
		}else{
			for(int j=1;j<=L_prey.size();j++){
				selectiv[i][j] /= ss;
			}	
			

		}

	}


}

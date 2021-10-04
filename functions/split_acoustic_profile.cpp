#include <admodel.h>

void split_acoustic_profile(dvector& var,dvector sa,dvector fact){
	dvector prod = elem_prod(sa,fact);
	double tot = sum(prod);
	var = prod/tot;


}

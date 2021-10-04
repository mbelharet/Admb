#include <admodel.h>

using namespace std;

void assign_ind_to_obs(dvector& ind, dvector obs){
	int bottom = obs.size();
 for(int z=1;z<=bottom;z++){
  if(obs[z]==9999.){
	  ind[z] = 0;
  }else{
	  ind[z] = 1;
  }
 }

}

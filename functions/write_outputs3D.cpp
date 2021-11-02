#include <admodel.h>

using namespace std;

void write_outputs3D(adstring filename, dvar3_array var,int bottom, int ngroups, char period[]){

	if((strcmp(period,"d"))==0 || (strcmp(period,"dn"))==0){
   
        	ofstream monFlux(filename + "_d" +".txt");
        		for(int z=1; z<=bottom;z++){
				for(int g(1);g<=ngroups;g++){
            				monFlux << var[1][g][z] << " ";
				}
				monFlux <<endl;
        		 }
		monFlux.close();

	}
       	if((strcmp(period,"n"))==0 || (strcmp(period,"dn"))==0){

		ofstream monFlux(filename + "_n" +".txt");
                        for(int z=1; z<=bottom;z++){
				for(int g(1);g<=ngroups ; g++){
                                        monFlux << var[2][g][z] << " ";
                                }
                                monFlux <<endl;
                         }
		monFlux.close();

	}
	if((strcmp(period,"n"))!=0 && (strcmp(period,"dn"))!=0){
		cout<< "ERROR ! : the last argument of the function ""write_outputs3D"" should be either ""d"" (for daytime) , ""n"" (for night-time) or ""dn"" for both " <<  endl;
	}

        
}       

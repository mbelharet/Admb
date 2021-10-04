#include <admodel.h>

using namespace std;

void write_outputs3D(adstring filename, dvar3_array var,int bottom, char period[]){

	if((strcmp(period,"d"))==0 || (strcmp(period,"dn"))==0){
   
        	ofstream monFlux(filename + "_d" +".txt");
        		for(int z=1; z<=bottom;z++){
            			monFlux << var[1][1][z] << " " << var[1][2][z] << " " << var[1][3][z] << endl;
        		 }
		monFlux.close();

	}
       	if((strcmp(period,"n"))==0 || (strcmp(period,"dn"))==0){

		ofstream monFlux(filename + "_n" +".txt");
                        for(int z=1; z<=bottom;z++){
                                monFlux << var[2][1][z] << " " << var[2][2][z] << " " << var[2][3][z] << endl;
                         }
		monFlux.close();

	}
	if((strcmp(period,"n"))!=0 && (strcmp(period,"dn"))!=0){
		cout<< "ERROR ! : the last argument of the function ""write_outputs3D"" should be either ""d"" (for daytime) , ""n"" (for night-time) or ""dn"" for both " <<  endl;
	}

        
}       

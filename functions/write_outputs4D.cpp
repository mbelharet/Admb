#include <admodel.h>

using namespace std;

void write_outputs4D(adstring filename, dvar4_array var,int bottom, ivector len, char period[]){

	if((strcmp(period,"d"))==0 || (strcmp(period,"dn"))==0){
		for(int s=len[1]; s<=len[2]; s++){
   
        		ofstream monFlux(filename + "_" + str(s) + "_d" +".txt");
        			for(int z=1; z<=bottom;z++){
            				monFlux << var[1][1][z][s] << " " << var[1][2][z][s] << " " << var[1][3][z][s] << endl;
        		 	}
			monFlux.close();

		}

	}
       	if((strcmp(period,"n"))==0 || (strcmp(period,"dn"))==0){

		for(int s=len[1]; s<=len[2]; s++){

			ofstream monFlux(filename + "_" + str(s)  + "_n" +".txt");
                        	for(int z=1; z<=bottom;z++){
                                	monFlux << var[2][1][z][s] << " " << var[2][2][z][s] << " " << var[2][3][z][s] << endl;
                         	}
			monFlux.close();
		}

	}
	if((strcmp(period,"n"))!=0 && (strcmp(period,"dn"))!=0){
		cout<< "ERROR ! : the last argument of the function ""write_outputs3D"" should be either ""d"" (for daytime) , ""n"" (for night-time) or ""dn"" for both " <<  endl;
	}

        
}       

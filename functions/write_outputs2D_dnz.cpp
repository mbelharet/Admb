#include <admodel.h>

using namespace std;

void write_outputs2D_dnz(adstring filename, dvar_matrix var){

	int nb_row = var.rowmax();
	int nb_col = var.colmax();
	ofstream monFlux(filename + ".txt");
	for(int z=1; z<=nb_col;z++){
		for(int g=1; g<=nb_row;g++){
 	    		monFlux << var[g][z] << " " ;
		}
		monFlux << endl;
 	 }
       
	monFlux.close();

}

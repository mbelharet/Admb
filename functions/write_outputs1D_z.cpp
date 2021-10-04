#include <admodel.h>

using namespace std;

void write_outputs1D_z(adstring filename, dvar_vector var){
	int bottom = var.size();
        ofstream monFlux(filename + ".txt");
        for(int z=1; z<=bottom;z++){
            monFlux << var[z] << endl;
         }

        monFlux.close();

}


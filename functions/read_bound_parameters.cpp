#include <iostream>
#include <fstream>
#include<iomanip>
#include <sstream>
#include <limits>
#include <admodel.h>

using namespace std;

void read_bound_parameters(adstring filename,double& SIGM_LIGHT1_min,double& SIGM_LIGHT1_max,double& SIGM_LIGHT1_phase,double& OPT_LIGHT1_min,double& OPT_LIGHT1_max,double& OPT_LIGHT1_phase,double& ADVz1_min,double& ADVz1_max,double& ADVz1_phase,double& DIFFz1_min,double& DIFFz1_max,double& DIFFz1_phase){
  string line;
 // int const bottom(749);
  //ifstream Flux(filename.c_str());
  ifstream Flux(filename);
  if(Flux){
     Flux.seekg(0,Flux.beg);//ios::beg); //se mettre au début du fichier
    
      // while(!Flux.eof()){  // si le fin du fichier n'a pas été atteinte
      Flux.ignore(numeric_limits<streamsize>::max(),'\n');
      Flux >> SIGM_LIGHT1_min;
      Flux >> SIGM_LIGHT1_max;
      Flux >> SIGM_LIGHT1_phase;
      
      Flux >> line;
      Flux.ignore();
      
      Flux >> OPT_LIGHT1_min;
      Flux >> OPT_LIGHT1_max;
      Flux >> OPT_LIGHT1_phase;

      Flux >> line;
      Flux.ignore();

      Flux >> ADVz1_min;
      Flux >> ADVz1_max;
      Flux >> ADVz1_phase;

      Flux >> line;
      Flux.ignore();

      Flux >> DIFFz1_min;
      Flux >> DIFFz1_max;
      Flux >> DIFFz1_phase;      

      Flux.close();

   }
  else{
           cout<<"Error : Enable to read the file  " << filename  << " !" << endl;
  }
}


void read_bound_parameters(adstring filename,double& SIGM_LIGHT2_min,double& SIGM_LIGHT2_max,double& SIGM_LIGHT2_phase,double& OPT_LIGHT2_min,double& OPT_LIGHT2_max,double& OPT_LIGHT2_phase,double& ADVz2_min,double& ADVz2_max,double& ADVz2_phase,double& DIFFz2_min,double& DIFFz2_max,double& DIFFz2_phase, double& SIGM_LIGHT3_min,double& SIGM_LIGHT3_max,double& SIGM_LIGHT3_phase,double& OPT_LIGHT3_min,double& OPT_LIGHT3_max,double& OPT_LIGHT3_phase,double& ADVz3_min,double& ADVz3_max,double& ADVz3_phase,double& DIFFz3_min,double& DIFFz3_max,double& DIFFz3_phase){
  string line;
 // int const bottom(749);
  //ifstream Flux(filename.c_str());
  ifstream Flux(filename);
  if(Flux){
     Flux.seekg(0,Flux.beg);//ios::beg); //se mettre au début du fichier

      // while(!Flux.eof()){  // si le fin du fichier n'a pas été atteinte
      Flux.ignore(numeric_limits<streamsize>::max(),'\n');
      Flux >> SIGM_LIGHT2_min;
      Flux >> SIGM_LIGHT2_max;
      Flux >> SIGM_LIGHT2_phase;

      Flux >> line;
      Flux.ignore();

      Flux >> SIGM_LIGHT3_min;
      Flux >> SIGM_LIGHT3_max;
      Flux >> SIGM_LIGHT3_phase;

      Flux >> line;
      Flux.ignore();

      Flux >> OPT_LIGHT2_min;
      Flux >> OPT_LIGHT2_max;
      Flux >> OPT_LIGHT2_phase;

      Flux >> line;
      Flux.ignore();

      Flux >> OPT_LIGHT3_min;
      Flux >> OPT_LIGHT3_max;
      Flux >> OPT_LIGHT3_phase;

      Flux >> line;
      Flux.ignore();

      Flux >> ADVz2_min;
      Flux >> ADVz2_max;
      Flux >> ADVz2_phase;

      Flux >> line;
      Flux.ignore();

      Flux >> ADVz3_min;
      Flux >> ADVz3_max;
      Flux >> ADVz3_phase;

      Flux >> line;
      Flux.ignore();

      Flux >> DIFFz2_min;
      Flux >> DIFFz2_max;
      Flux >> DIFFz2_phase;

      Flux >> line;
      Flux.ignore();

      Flux >> DIFFz3_min;
      Flux >> DIFFz3_max;
      Flux >> DIFFz3_phase;



      Flux.close();

   }
  else{
           cout<<"Error : Enable to read the file  " << filename  << " !" << endl;
  }
}





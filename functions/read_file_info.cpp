#include <iostream>
#include <fstream>
#include<iomanip>
#include <sstream>
#include <admodel.h>

using namespace std;

void read_file_info(adstring filename, double& Time, double& Lat, double& Lon, int& bottom, double& deltaz ){
  double line(0.);
 // int const bottom(749);
  //ifstream Flux(filename.c_str());
  ifstream Flux(filename);
  if(Flux){
     Flux.seekg(0,Flux.beg);//ios::beg); //se mettre au début du fichier
     Flux.ignore();
      // while(!Flux.eof()){  // si le fin du fichier n'a pas été atteinte
      Flux >> Time;
      Flux >> Lat;
      Flux >> Lon;
      Flux >> bottom;
      Flux >> deltaz;
     
      Flux.close();

   }
  else{
           cout<<"Error : Enable to read the file  " << filename  << " !" << endl;
  }
}


void read_file_info(adstring filename, double& Time, double& Lat, double& Lon, int& bottom, double& deltaz, double& DL , double& alpha1, double& alpha3){
  double line(0.);
 // int const bottom(749);
  //ifstream Flux(filename.c_str());
  ifstream Flux(filename);
  if(Flux){
     Flux.seekg(0,Flux.beg);//ios::beg); //se mettre au début du fichier
     Flux.ignore();
      // while(!Flux.eof()){  // si le fin du fichier n'a pas été atteinte
      Flux >> Time;
      Flux >> Lat;
      Flux >> Lon;
      Flux >> bottom;
      Flux >> deltaz;
      Flux >> DL;
      Flux >>alpha1;
      Flux >> alpha3;

      Flux.close();

   }
  else{
           cout<<"Error : Enable to read the file  " << filename  << " !" << endl;
  }
}


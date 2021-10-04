#include <iostream>
#include <vector>
#include <fstream>
#include<iomanip>
#include <sstream>
#include <admodel.h>

using namespace std;

void read_file(adstring pathway, adstring filename, dvector& tab, int bottom){
  double const  EPS(1.e-35);
  double line(0.);
  //ifstream Flux(filename.c_str());
  
  ifstream Flux;
  Flux.open(pathway + filename);

  if(!Flux){
	 Flux.close();
	 Flux.open(pathway + "reanalysis_" + filename);
  }

  if(Flux){
     Flux.seekg(0,Flux.beg);//ios::beg); //se mettre au début du fichier
     Flux.ignore();
      // while(!Flux.eof()){  // si le fin du fichier n'a pas été atteinte
      int z(1);
       while(Flux.peek()!=EOF){

         Flux >> line;
         //tab.push_back(line);a
	 if(z<=bottom){
	 tab[z] = line;
	 z++;
	 }
       }
     //tab.pop_back();
     Flux.close();


   }
  else{
   cout<<"Error : Enable to read the file  " << filename  << " !" << endl;
  }
}


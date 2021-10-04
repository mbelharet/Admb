#include <admodel.h>
#include <stdlib.h>
using namespace std;

void initialize_parameters(dvariable& SIGM_LIGHT1, dvariable& SIGM_LIGHT2, dvariable& SIGM_LIGHT3,
                           dvariable& OPT_LIGHT1, dvariable& OPT_LIGHT2, dvariable& OPT_LIGHT3,
                           dvariable& SIGM_TCOR0, dvariable& Ta, 
			   dvariable& OXYRESP2, dvariable& OXYRESP3, dvariable& OXYLIM2, dvariable& OXYLIM3,
                           dvariable& ADVz1, dvariable& ADVz2, dvariable& ADVz3,
                           dvariable& DIFFz1, dvariable& DIFFz2, dvariable& DIFFz3,
			   dvariable& c1, dvariable& c2,
                           int id1,int id2,int id3,
                           int id4,int id5,int id6,
                           int id7,int id8,
			   int id9,int id10,int id11,int id12,
			   int id13,int id14,int id15,
			   int id16,int id17,int id18,
			   int id19,int id20,
			   int nb_par){
	ifstream Flux;
	Flux.open("initial_parameters.txt");

	if(Flux){
    		Flux.seekg(0,Flux.beg);//ios::beg); //se mettre au début du fichier
     		Flux.ignore();
      		// while(!Flux.eof()){  // si le fin du fichier n'a pas été atteinte
		string line;
		int z=0;
		while(getline(Flux,line)){
			//getline(Flux,line);
			if(z%2==0){
				if(z==0){
					if(id1==1){
						Flux >> SIGM_LIGHT1;
					}else{
						Flux >> line;
					}
				}else if(z==2){
					if(id2==1){
                                                Flux >> SIGM_LIGHT2;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==4){
					if(id3==1){
                                                Flux >> SIGM_LIGHT3;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==6){
					if(id4==1){
                                                Flux >> OPT_LIGHT1;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==8){
					if(id5==1){
                                                Flux >> OPT_LIGHT2;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==10){
					if(id6==1){
                                                Flux >> OPT_LIGHT3;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==12){
					if(id7==1){
                                                Flux >> SIGM_TCOR0;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==14){
					if(id8==1){
                                                Flux >> Ta;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==16){
					if(id9==1){
                                                Flux >> OXYRESP2;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==18){
                                        if(id10==1){
                                                Flux >> OXYRESP3;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==20){
					if(id11==1){
                                                Flux >> OXYLIM2;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==22){
                                        if(id12==1){
                                                Flux >> OXYLIM3;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==24){
					if(id13==1){
                                                Flux >> ADVz1;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==26){
					if(id14==1){
                                                Flux >> ADVz2;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==28){
					if(id15==1){
                                                Flux >> ADVz3;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==30){
					if(id16==1){
                                                Flux >> DIFFz1;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==32){
					if(id17==1){
                                                Flux >> DIFFz2;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==34){
					if(id18==1){
                                                Flux >> DIFFz3;
                                        }else{
                                                Flux >> line;
                                        }
				}else if(z==36){
                                        if(id19==1){
                                                Flux >> c1;
                                        }else{
                                                Flux >> line;
                                        }
                                }else if(z==38){
                                        if(id20==1){
                                                Flux >> c2;
                                        }else{
                                                Flux >> line;
                                        }
                                }

			}
			z++;


		}

		/*for(int z(1);z<=2*nb_par+1;z=z+1){
			//std::getline(Flux,line);
       		//while(Flux.peek()!=EOF){
	

			if(z==3){
				if(id1==1){
					//Flux >> SIGM_LIGHT1;
					std::getline(Flux,line);
					cout<<line<<endl;
					double a = atof("24");
				}
			}else if(z==3){
				if(id2==1){
					Flux >> SIGM_LIGHT2 >> line;
				}
			}else if(z==5){
                                if(id3==1){
                                        Flux >> SIGM_LIGHT3 >> line;
				}
			}else if(z==7){
                                if(id4==1){
                                        Flux >> OPT_LIGHT1;
				}
			}else if(z==9){
                                if(id5==1){
                                        Flux >> OPT_LIGHT2;
				}
			}else if(z==11){
                                if(id6==1){
                                        Flux >> OPT_LIGHT3;
				}
			}else if(z==13){
                                if(id7==1){
                                        Flux >> SIGM_TCOR0;
				}
			}else if(z==15){
                                if(id8==1){
                                        Flux >> Ta;
				}
			}else if(z==17){
                                if(id9==1){
                                        Flux >> OXYRESP;
				}
			}else if(z==19){
                                if(id10==1){
                                        Flux >> OXYLIM;
				}
			}else if(z==21){
                                if(id11==1){
                                        Flux >> ADVz1;
				}
			}else if(z==23){
                                if(id12==1){
                                        Flux >> ADVz2;
				}
			}else if(z==25){
                                if(id13==1){
                                        Flux >> ADVz3;
				}
			}else if(z==27){
                                if(id14==1){
                                        Flux >> DIFFz1;
				}
			}else if(z==29){
                                if(id15==1){
                                        Flux >> DIFFz2;
				}
			}else if(z==31){
                                if(id16==1){
                                        Flux >> DIFFz3;
				}
			}else{
				std::getline(Flux,line);
			}
			

			//z++;
			cout << "z = " << z << endl;
			cout << "Flux = " << line << endl;	
       		}*/



     	//tab.pop_back();
     	Flux.close();
	}else{
   		cout<<"Error : Enable to read the file: initial_parameters.txt !" << endl;
  	}



}

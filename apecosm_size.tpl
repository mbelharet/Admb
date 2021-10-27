GLOBALS_SECTION
 #include <fstream>
 #include <vector>
 #include <functions/read_file.cpp>
 #include <functions/get_temp_oxy_pref.cpp>
 #include <functions/get_light_pref.cpp>
 #include <functions/calculate_adv_diff_bis.cpp>
 #include <functions/calculate_obj_function.cpp>
 #include <functions/write_outputs2D_dnz.cpp>
 #include <functions/write_outputs3D.cpp>
 #include <functions/write_outputs1D_z.cpp>
 #include <functions/write_outputs4D.cpp>
 #include <functions/split_acoustic_profile.cpp>
 #include <functions/update_habitat_env.cpp>
 #include <functions/calculate_selectivity.cpp>
 #include <functions/calculate_normalized_profile.cpp>
 #include <functions/calculate_habitat_env.cpp>

  //declaration of global parameters
  adstring pathway;
  adstring pathway_o;
  int L_size;
  bool include_forage(false);


//**********************************************************************
   
DATA_SECTION
  init_adstring main_path
  init_adstring project
  init_number nb_clstr
  init_number bottom
  init_adstring zone
  init_number Tref
  init_number EPS
  init_number p
  //init_number nfactor
  init_number DzPHY
  //init_number EYE_DIAM_ALLOM1
  init_vector len(1,9)
  //init_number SIGM_TCOR0
  //init_number SIGM_LIGHT1
  //init_number OPT_LIGHT1
  //init_number ADVz1
  //init_number DIFFz1
  init_number nb_site_t
  init_number a1
  init_number a2
  init_number rho1
  init_number rho2
  init_number gamma

 LOC_CALCS
    L_size = len.size();
    pathway = main_path + "/data/" + project + "/"; //  + sec_path + project + "/";
    pathway_o = main_path + "/outputs/" + project + "/";

 END_CALCS

 //------------------------------------
 // Declaration of variables that are not depending on 
 // calibrated parameters 
 //-----------------------------------------

  //number len
  vector temper_d(1,bottom)
  vector temper_n(1,bottom)
  vector oxy_d(1,bottom)
  vector oxy_n(1,bottom)
  vector light(1,bottom)
  vector light_d(1,bottom)
  vector light_n(1,bottom)
  vector sA_d(1,bottom)
  vector sA_n(1,bottom)
  vector depth(1,bottom)
  vector DL_d(1,nb_site_t) //(1,nb_clstr)
  vector DL_n(1,nb_site_t)
  vector par_att(1,nb_site_t)
  vector alpha1(1,nb_site_t) //(1,nb_clstr)
  vector alpha3(1,nb_site_t) // (1,nb_clstr)
  vector clusters(1,nb_clstr)
  vector fact(1,bottom)
  vector NFACTOR(1,nb_clstr)
  matrix phi(1,bottom,1,L_size)
  matrix selectiv(1,L_size,1,L_size)

//***************************************************************************************************
INITIALIZATION_SECTION
  //SIGM_LIGHT2 5.e-07
  //SIGM_LIGHT3 1.e-07
  //OPT_LIGHT2 5.e-08
  //OPT_LIGHT3 3.0e-08
  //Ta 5020
  //OXYRESP2 80
  //OXYRESP3 30
  //OXYLIM2 1
  //OXYLIM3 0.1
  //ADVz2 20
  //ADVz3 20
  //c1 0.5
  //c2 0.5
  //nfactor 1e-6
  
//*********************************************************************


PARAMETER_SECTION

  objective_function_value f
   vector light2(1,bottom)
   vector temper_pref(1,bottom)
   vector temper_pref_epi(1,bottom)
   matrix oxy_pref(1,3,1,bottom)
   4darray light_pref(1,2,1,3,1,bottom,1,L_size)
   matrix f_food(1,2,1,bottom)
   4darray habitat_env(1,2,1,3,1,bottom,1,L_size)
   4darray profile(1,2,1,3,1,bottom,1,L_size)
   3darray profiletot(1,2,1,3,1,L_size)
   4darray profile_norm(1,2,1,3,1,bottom,1,L_size)
   3darray prof_mod_g(1,2,1,3,1,bottom)
   3darray sum_phi_p(1,2,1,3,1,bottom)
   matrix sum_sum_phi_p(1,2,1,3)
   

   init_bounded_number OXYRESP2(0.,100,1); //WOA (0.,100,1)
   init_bounded_number OXYLIM2(0.01,1,1); // WOA (0,3,1)
   init_bounded_number OXYRESP3(0.,100,-1); //WOA (0.,100,-1)
   init_bounded_number OXYLIM3(0.,1,-1); 
   init_bounded_number Ta(4000,7000,-1);

   init_bounded_number SIGM_LIGHT2(1e-7,1e-2,1) // WOA  (1.e-8,1.e-1,1) ; NEMO (1e-8,1e-2,1)
   init_bounded_number SIGM_LIGHT3(1e-7,1e-2,1) // WOA  (1.e-14,1.e-7,1) ; NEMO (1e-14,1e-7,1)
   init_bounded_number OPT_LIGHT2(1.e-7,1.e-2,1) // WOA (1.e-8,1.e-1) ; NEMO (1.e-8,1.e-2,1)
   init_bounded_number OPT_LIGHT3(1.e-7,1.e-2,1) // WOA  (1.e-14,1.e-7,1); NEMO (1.e-14,1.e-7,1)

   init_bounded_number ADVz3(1e-2,100,1) //WOA (1e-1,100,1) ; NEMO (1e-2,100,1)
   init_bounded_number ADVz2(1e-2,100,1) //WOA (1e-1,100,1); NEMO (1e-2,100,1)
   init_bounded_number DIFFz3(1e-2,200,1)//WOA (1e-1,200,1); NEMO (1e-2,200,1)
   init_bounded_number DIFFz2(1e-2,200,1) //WOA (1e-1,200,1); NEMO (1e-2,200,1)

   init_bounded_number c1(0,2,-1) // WOA (0,2,1) ; NEMO (0,2,1):1

   init_bounded_number c2(0,2,-1) //WOA (0,2,1) ; NEMO (0,2,1) 

   init_bounded_number Coxy(0,5,-1) //WOA (0,1,1)
   init_bounded_number ko2_max(0,2,-1);  //(0,2,1);
   init_bounded_number a_o2(5,5,-1); //(1,10,1);

   init_bounded_number EYE_DIAM_ALLOM1(0.,0.,-1)
   init_bounded_number EYE_DIAM_ALLOM2(0.0,0.5,-1)
   init_bounded_number EYE_DIAM_ALLOM3(0.0,0.5,-1)

   init_bounded_number SIGM_TCOR0(0.01,1,1)
   init_bounded_number SIGM_LIGHT1(1e-2,1e4,1)
   init_bounded_number OPT_LIGHT1(1e-2,1e3,1)
   init_bounded_number ADVz1(0.1,100,1)
   init_bounded_number DIFFz1(0.01,200,1)

 LOC_CALCS
    ivector ph(1,nb_clstr);
    ph.fill_seqadd(2,1);
    dvector a_min(1,nb_clstr);
    a_min.fill_seqadd(1,0);
    a_min = 1.e-9 * a_min;

    dvector a_max(1,nb_clstr);
    a_max.fill_seqadd(1,0);
    a_max = 1.e-3 * a_max;
 END_CALCS

   //init_bounded_vector EYE_DIAM_ALLOM(1,3,0.8,1,2);
   //init_bounded_number_vector nfactor(1,nb_clstr,a_min,a_max,ph);   //(1,nb_clstr,1.e-9,3.e-6,2)
   init_bounded_number nfactor(1e-5,1e-5,-1); //(1e-7,1e-4,1); 

      
      
   vector SIGM_LIGHT(1,3)
   vector OPT_LIGHT(1,3)
   vector ADVz(1,3)
   vector DIFFz(1,3)
   vector EYE_DIAM_ALLOM(1,3)
   matrix ratio_adv_diff(1,3,1,L_size)
   matrix diffz(1,3,1,L_size)
   matrix ratio_adv_diff2(1,3,1,L_size)
   vector OXYRESP(1,2)
   vector OXYLIM(1,2)
   matrix eyesurf(1,3,1,L_size)
   matrix J(1,2,1,nb_clstr)


//********************************************************************************

PRELIMINARY_CALCS_SECTION

  adstring zone_ = "selected"; // omz, Nomz, selected
  read_file(pathway, "depth.txt", depth, bottom);
  read_file(pathway, "cluster_list_" + zone_ + "_bis.txt", clusters, nb_clstr);
  read_file(pathway, "DL_d.txt", DL_d, nb_site_t); //nb_clstr
  read_file(pathway, "DL_n.txt", DL_n, nb_site_t); 
  read_file(pathway,"alpha1.txt", alpha1, nb_site_t);
  read_file(pathway,"alpha3.txt", alpha3, nb_site_t); 
  
  for(int s(1);s<=L_size;s++){
	dvector phi_(1,bottom);
	read_file(pathway, "phi_" + str(s) + ".txt", phi_, bottom);
	for(int z(1);z<=phi_.size();z++){
		phi[z][s] = phi_[z];
	}
  }
  //read_file(pathway, "PAR_attenuation.txt", par_att, nb_site_t);
  //read_file(pathway, "NFACTOR.txt", NFACTOR, nb_clstr);


//**************************************************************************************************

BETWEEN_PHASES_SECTION

  if(current_phase()==2){
        cout << "coucou je commence la phase 2" << endl;
  }


//********************************************************************************

PROCEDURE_SECTION
 //f=0.;

  OPT_LIGHT[1] = OPT_LIGHT1;
  OPT_LIGHT[2] = OPT_LIGHT2;
  OPT_LIGHT[3] = OPT_LIGHT3;
  SIGM_LIGHT[1] = SIGM_LIGHT1;
  SIGM_LIGHT[2] = SIGM_LIGHT2;
  SIGM_LIGHT[3] = SIGM_LIGHT3;

  OXYRESP[1] = OXYRESP2;
  OXYRESP[2] = OXYRESP3;
  OXYLIM[1] = OXYLIM2;
  OXYLIM[2] = OXYLIM3;

  ADVz[1] = ADVz1;
  ADVz[2] = ADVz2;
  ADVz[3] = ADVz3;
  DIFFz[1] = DIFFz1;
  DIFFz[2] =DIFFz2;
  DIFFz[3] =DIFFz3;

  EYE_DIAM_ALLOM[1] = EYE_DIAM_ALLOM1;
  EYE_DIAM_ALLOM[2] = EYE_DIAM_ALLOM2;
  EYE_DIAM_ALLOM[3] = EYE_DIAM_ALLOM3;
  dvar_vector nfactor_(1,2);
  nfactor_[1] = 1.0;
  nfactor_[2] = nfactor;

  calculate_adv_diff_bis(ratio_adv_diff, diffz, ratio_adv_diff2,eyesurf, ADVz, DIFFz, DzPHY,len, EYE_DIAM_ALLOM);
  //calculate_selectivity(selectiv, len, len, a1, a2, rho1, rho2, gamma); // selectivité normalisée
	for(int i(1);i<=L_size;i++){
		selectiv[i][i] = 1;
	}


    for(int i_clstr=1; i_clstr<= nb_clstr; i_clstr++){       //<= nb_clstr

       int nb_ = clusters[i_clstr];
       adstring nb = str(nb_);
	
        
       read_file(pathway, "temp_d_" + nb + ".txt",temper_d,bottom);
       read_file(pathway, "temp_n_" + nb + ".txt",temper_n,bottom);
       read_file(pathway, "oxy_d_" + nb + ".txt",oxy_d,bottom);
       read_file(pathway, "oxy_n_" + nb + ".txt",oxy_n,bottom);
       read_file(pathway, "par_d_" + nb + ".txt",light_d,bottom);
       read_file(pathway, "par_n_" + nb + ".txt",light_n,bottom);
       read_file(pathway, "sA_d_" + nb + ".txt",sA_d,bottom); // Déjà normalisés
       read_file(pathway, "sA_n_" + nb + ".txt",sA_n,bottom); // Déjà normalisés
	
      for(int g(1); g<=3;g++){

		for(int dn(1); dn<=2; dn++){
				dvariable temper_1;
				dvariable temper_z;
				dvariable oxy_z;
				dvariable oxy_m(0.);
				dvariable DL;

				if(dn==1){
					temper_1 = temper_d[1];
					light = light_d;
					DL = DL_d[nb_];
				}else{
					temper_1 = temper_n[1];
					light = light_d;
					DL = 1- DL_n[nb_];
				}
					
			for(int s(3); s<=7; s++){ //L_size

				profiletot[dn][g][s] = 0 ;

				for(int z(1); z<=bottom; z++){
					if(dn==1){
						temper_z = temper_d[z];
						oxy_z = oxy_d[z];
						if(z>=21){
							oxy_m =  (oxy_d[z] +  oxy_d[z-1])/2;}

					}else{
						temper_z = temper_n[z];
						oxy_z = oxy_n[z];
						if(z>=21){
						oxy_m =  (oxy_n[z] +  oxy_n[z-1])/2;}
					}

					get_temp_oxy_pref(temper_pref, oxy_pref,temper_1,temper_z, oxy_z, Ta, Tref, SIGM_TCOR0, OXYRESP, OXYLIM, z );
					get_light_pref(light_pref, light, SIGM_LIGHT, OPT_LIGHT, DL, nfactor_, EPS, eyesurf[g][s], oxy_m, ko2_max, a_o2, dn, g, z, s);
					calculate_habitat_env(habitat_env, light_pref, temper_pref, oxy_pref, profile, profiletot, ratio_adv_diff2, diffz, ratio_adv_diff, DzPHY, dn, g, z, s );
	
				} // boucle z

				calculate_normalized_profile(profile_norm, profile, profiletot, dn, g, s, bottom );
				
			} // boucle s

	//****************************************************************************************************************************************************

		// this part is run only if the foraging is taken into account 

	//******************************************************************************************************************************************************
		if(include_forage){
			for(int s(3); s<=7; s++){

				profiletot[dn][g][s] = 0.0 ;

				for(int z(1); z<=bottom; z++){
					if((g==2) & (dn==2)){
                        			update_habitat_env(habitat_env, profile_norm[2][1][z][s], selectiv, profile, profiletot, ratio_adv_diff2, diffz, ratio_adv_diff,DzPHY, c1, dn, g, s, z, L_size);
					}

					if((g==3) & (dn==1)){
                                		update_habitat_env(habitat_env, profile_norm[1][2][z][s], selectiv, profile, profiletot, ratio_adv_diff2, diffz, ratio_adv_diff,DzPHY, c2, dn, g, s, z, L_size);
                        		}
				} // boucle z
				if(((g==2) & (dn==2)) | ((g==3) & (dn==1))){
					calculate_normalized_profile(profile_norm, profile, profiletot, dn, g, s, bottom );
				}
			} // boucle s

		} // end foraging condition

	//**************************************************************************************************************************************************************


		// Prise en compte des paramètres acoustiques
			sum_sum_phi_p[dn][g] = 0.0;

			for(int z(1); z<=bottom; z++){

				sum_phi_p[dn][g][z] = 0.0;

				for(int s(3); s<=7; s++){
					sum_phi_p[dn][g][z] += phi[z][s] * profile_norm[dn][g][z][s]; //phi[z][s]
					
				} // boucle s

				sum_sum_phi_p[dn][g] += sum_phi_p[dn][g][z];

			} // boucle z

		// Normalisation finale
			for(int z(1); z<=bottom; z++){
				prof_mod_g[dn][g][z] = sum_phi_p[dn][g][z] / sum_sum_phi_p[dn][g];
				//cout << "z = " << z << " : light = " << light[z] << endl;
			} // boucle z

              } // fin de la boucle dn

		//cout << "g = " << str(g) << endl;
      }// fin de la boucle g
		// La fonction objective

		f += calculate_obj_function(sA_d,sA_n, prof_mod_g, bottom, alpha1[nb_],alpha3[nb_]);

		//cout << f << endl;
	char period[] = "dn";
	ivector toto(1,2);
	toto[1] = 4;
	toto[2] = 4; 
	write_outputs3D("outputs/" + project +  "/" + zone +  "/profile_norm_by_group_" + nb ,prof_mod_g, bottom, period);
	//write_outputs4D("outputs/" + project +  "/" + zone +  "/light_pref_" + nb ,light_pref, bottom,toto,period);
	 //write_outputs2D_dnz("outputs/" + project  + "/" + zone + "/oxy_pref_" + nb , oxy_pref);

    } // boucle clstr




 


 //      write_outputs2D_dnz("outputs/" + project  + "/" + zone + "/profile_norm_total_" + nb + "_" + ss, profile_g_comb);
 //     char period[] = "dn";
 //     write_outputs3D("outputs/" + project + "/" + zone + "/profile_norm_by_group_" + nb + "_" + ss, profile_norm,bottom, period);
      
  
	//write_outputs3D("outputs/" + project +  "/" + zone +  "/light_pref_" + nb ,light_pref, bottom,period);
        //write_outputs1D_z("outputs/" + project +  "/" + zone +  "/profile_size_1_" + nb , profile_size_1);
	//write_outputs3D("outputs/" + project +  "/" + zone +  "/habitat_env_" + nb , habitat_env, bottom,period);
         //write_outputs3D("outputs/" + project +  "/" + zone +  "/profile_" + nb , profile, bottom,period);

      //write_outputs3D("outputs/" + project + "/habitat_env_" + nb, habitat_env,bottom, period);
      ////write_outputs3D("outputs/" + project + "/profile_" + nb, profile,bottom, period);
     //write_outputs2D_dnz("outputs/" + project + "/pref_oxy_" + nb, oxy_pref);
     //write_outputs2D_dnz("outputs/" + project + "/pref_food_" + nb, f_food);
     // write_outputs1D_z("outputs/" + project +  "/light_pref_1_" + nb , light_pref_1);
      //write_outputs1D_z("outputs/" + project +  "/profile1_" + nb , light2);
      //write_outputs3D("outputs/" + project + "/pref_light_" + nb , light_pref, bottom, period);
  	
  




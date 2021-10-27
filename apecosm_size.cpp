#ifdef DEBUG
  #ifndef __SUNPRO_C
    #include <cfenv>
    #include <cstdlib>
  #endif
#endif
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
   
#include <admodel.h>
#include <contrib.h>

  extern "C"  {
    void ad_boundf(int i);
  }
#include <apecosm_size.htp>

model_data::model_data(int argc,char * argv[]) : ad_comm(argc,argv)
{
  main_path.allocate("main_path");
  project.allocate("project");
  nb_clstr.allocate("nb_clstr");
  bottom.allocate("bottom");
  zone.allocate("zone");
  Tref.allocate("Tref");
  EPS.allocate("EPS");
  p.allocate("p");
  DzPHY.allocate("DzPHY");
  len.allocate(1,9,"len");
  nb_site_t.allocate("nb_site_t");
  a1.allocate("a1");
  a2.allocate("a2");
  rho1.allocate("rho1");
  rho2.allocate("rho2");
  gamma.allocate("gamma");
    L_size = len.size();
    pathway = main_path + "/data/" + project + "/"; //  + sec_path + project + "/";
    pathway_o = main_path + "/outputs/" + project + "/";
  temper_d.allocate(1,bottom);
  temper_n.allocate(1,bottom);
  oxy_d.allocate(1,bottom);
  oxy_n.allocate(1,bottom);
  light.allocate(1,bottom);
  light_d.allocate(1,bottom);
  light_n.allocate(1,bottom);
  sA_d.allocate(1,bottom);
  sA_n.allocate(1,bottom);
  depth.allocate(1,bottom);
  DL_d.allocate(1,nb_site_t);
  DL_n.allocate(1,nb_site_t);
  par_att.allocate(1,nb_site_t);
  alpha1.allocate(1,nb_site_t);
  alpha3.allocate(1,nb_site_t);
  clusters.allocate(1,nb_clstr);
  fact.allocate(1,bottom);
  NFACTOR.allocate(1,nb_clstr);
  phi.allocate(1,bottom,1,L_size);
  selectiv.allocate(1,L_size,1,L_size);
}

void model_parameters::initializationfunction(void)
{
}

model_parameters::model_parameters(int sz,int argc,char * argv[]) : 
 model_data(argc,argv) , function_minimizer(sz)
{
  initializationfunction();
  f.allocate("f");
  prior_function_value.allocate("prior_function_value");
  likelihood_function_value.allocate("likelihood_function_value");
  light2.allocate(1,bottom,"light2");
  #ifndef NO_AD_INITIALIZE
    light2.initialize();
  #endif
  temper_pref.allocate(1,bottom,"temper_pref");
  #ifndef NO_AD_INITIALIZE
    temper_pref.initialize();
  #endif
  temper_pref_epi.allocate(1,bottom,"temper_pref_epi");
  #ifndef NO_AD_INITIALIZE
    temper_pref_epi.initialize();
  #endif
  oxy_pref.allocate(1,3,1,bottom,"oxy_pref");
  #ifndef NO_AD_INITIALIZE
    oxy_pref.initialize();
  #endif
  light_pref.allocate(1,2,1,3,1,bottom,1,L_size,"light_pref");
  #ifndef NO_AD_INITIALIZE
    light_pref.initialize();
  #endif
  f_food.allocate(1,2,1,bottom,"f_food");
  #ifndef NO_AD_INITIALIZE
    f_food.initialize();
  #endif
  habitat_env.allocate(1,2,1,3,1,bottom,1,L_size,"habitat_env");
  #ifndef NO_AD_INITIALIZE
    habitat_env.initialize();
  #endif
  profile.allocate(1,2,1,3,1,bottom,1,L_size,"profile");
  #ifndef NO_AD_INITIALIZE
    profile.initialize();
  #endif
  profiletot.allocate(1,2,1,3,1,L_size,"profiletot");
  #ifndef NO_AD_INITIALIZE
    profiletot.initialize();
  #endif
  profile_norm.allocate(1,2,1,3,1,bottom,1,L_size,"profile_norm");
  #ifndef NO_AD_INITIALIZE
    profile_norm.initialize();
  #endif
  prof_mod_g.allocate(1,2,1,3,1,bottom,"prof_mod_g");
  #ifndef NO_AD_INITIALIZE
    prof_mod_g.initialize();
  #endif
  sum_phi_p.allocate(1,2,1,3,1,bottom,"sum_phi_p");
  #ifndef NO_AD_INITIALIZE
    sum_phi_p.initialize();
  #endif
  sum_sum_phi_p.allocate(1,2,1,3,"sum_sum_phi_p");
  #ifndef NO_AD_INITIALIZE
    sum_sum_phi_p.initialize();
  #endif
  OXYRESP2.allocate(0.,100,1,"OXYRESP2");
  OXYLIM2.allocate(0.01,1,1,"OXYLIM2");
  OXYRESP3.allocate(0.,100,-1,"OXYRESP3");
  OXYLIM3.allocate(0.,1,-1,"OXYLIM3");
  Ta.allocate(4000,7000,-1,"Ta");
  SIGM_LIGHT2.allocate(1e-7,1e-2,1,"SIGM_LIGHT2");
  SIGM_LIGHT3.allocate(1e-7,1e-2,1,"SIGM_LIGHT3");
  OPT_LIGHT2.allocate(1.e-7,1.e-2,1,"OPT_LIGHT2");
  OPT_LIGHT3.allocate(1.e-7,1.e-2,1,"OPT_LIGHT3");
  ADVz3.allocate(1e-2,100,1,"ADVz3");
  ADVz2.allocate(1e-2,100,1,"ADVz2");
  DIFFz3.allocate(1e-2,200,1,"DIFFz3");
  DIFFz2.allocate(1e-2,200,1,"DIFFz2");
  c1.allocate(0,2,-1,"c1");
  c2.allocate(0,2,-1,"c2");
  Coxy.allocate(0,5,-1,"Coxy");
  ko2_max.allocate(0,2,-1,"ko2_max");
  a_o2.allocate(5,5,-1,"a_o2");
  EYE_DIAM_ALLOM1.allocate(0.,0.,-1,"EYE_DIAM_ALLOM1");
  EYE_DIAM_ALLOM2.allocate(0.0,0.5,-1,"EYE_DIAM_ALLOM2");
  EYE_DIAM_ALLOM3.allocate(0.0,0.5,-1,"EYE_DIAM_ALLOM3");
  SIGM_TCOR0.allocate(0.01,1,1,"SIGM_TCOR0");
  SIGM_LIGHT1.allocate(1e-2,1e4,1,"SIGM_LIGHT1");
  OPT_LIGHT1.allocate(1e-2,1e3,1,"OPT_LIGHT1");
  ADVz1.allocate(0.1,100,1,"ADVz1");
  DIFFz1.allocate(0.01,200,1,"DIFFz1");
    ivector ph(1,nb_clstr);
    ph.fill_seqadd(2,1);
    dvector a_min(1,nb_clstr);
    a_min.fill_seqadd(1,0);
    a_min = 1.e-9 * a_min;
    dvector a_max(1,nb_clstr);
    a_max.fill_seqadd(1,0);
    a_max = 1.e-3 * a_max;
  nfactor.allocate(1e-5,1e-5,-1,"nfactor");
  SIGM_LIGHT.allocate(1,3,"SIGM_LIGHT");
  #ifndef NO_AD_INITIALIZE
    SIGM_LIGHT.initialize();
  #endif
  OPT_LIGHT.allocate(1,3,"OPT_LIGHT");
  #ifndef NO_AD_INITIALIZE
    OPT_LIGHT.initialize();
  #endif
  ADVz.allocate(1,3,"ADVz");
  #ifndef NO_AD_INITIALIZE
    ADVz.initialize();
  #endif
  DIFFz.allocate(1,3,"DIFFz");
  #ifndef NO_AD_INITIALIZE
    DIFFz.initialize();
  #endif
  EYE_DIAM_ALLOM.allocate(1,3,"EYE_DIAM_ALLOM");
  #ifndef NO_AD_INITIALIZE
    EYE_DIAM_ALLOM.initialize();
  #endif
  ratio_adv_diff.allocate(1,3,1,L_size,"ratio_adv_diff");
  #ifndef NO_AD_INITIALIZE
    ratio_adv_diff.initialize();
  #endif
  diffz.allocate(1,3,1,L_size,"diffz");
  #ifndef NO_AD_INITIALIZE
    diffz.initialize();
  #endif
  ratio_adv_diff2.allocate(1,3,1,L_size,"ratio_adv_diff2");
  #ifndef NO_AD_INITIALIZE
    ratio_adv_diff2.initialize();
  #endif
  OXYRESP.allocate(1,2,"OXYRESP");
  #ifndef NO_AD_INITIALIZE
    OXYRESP.initialize();
  #endif
  OXYLIM.allocate(1,2,"OXYLIM");
  #ifndef NO_AD_INITIALIZE
    OXYLIM.initialize();
  #endif
  eyesurf.allocate(1,3,1,L_size,"eyesurf");
  #ifndef NO_AD_INITIALIZE
    eyesurf.initialize();
  #endif
  J.allocate(1,2,1,nb_clstr,"J");
  #ifndef NO_AD_INITIALIZE
    J.initialize();
  #endif
}

void model_parameters::preliminary_calculations(void)
{

#if defined(USE_ADPVM)

  admaster_slave_variable_interface(*this);

#endif
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
}

void model_parameters::between_phases_calculations(void)
{
  if(current_phase()==2){
        cout << "coucou je commence la phase 2" << endl;
  }
}

void model_parameters::userfunction(void)
{
  f =0.0;
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
}

model_data::~model_data()
{}

model_parameters::~model_parameters()
{}

void model_parameters::report(const dvector& gradients){}

void model_parameters::final_calcs(void){}

void model_parameters::set_runtime(void){}

#ifdef _BORLANDC_
  extern unsigned _stklen=10000U;
#endif


#ifdef __ZTC__
  extern unsigned int _stack=10000U;
#endif

  long int arrmblsize=0;

int main(int argc,char * argv[])
{
    ad_set_new_handler();
  ad_exit=&ad_boundf;
    gradient_structure::set_NO_DERIVATIVES();
#ifdef DEBUG
  #ifndef __SUNPRO_C
std::feclearexcept(FE_ALL_EXCEPT);
  #endif
#endif
    gradient_structure::set_YES_SAVE_VARIABLES_VALUES();
    if (!arrmblsize) arrmblsize=15000000;
    model_parameters mp(arrmblsize,argc,argv);
    mp.iprint=10;
    mp.preliminary_calculations();
    mp.computations(argc,argv);
#ifdef DEBUG
  #ifndef __SUNPRO_C
bool failedtest = false;
if (std::fetestexcept(FE_DIVBYZERO))
  { cerr << "Error: Detected division by zero." << endl; failedtest = true; }
if (std::fetestexcept(FE_INVALID))
  { cerr << "Error: Detected invalid argument." << endl; failedtest = true; }
if (std::fetestexcept(FE_OVERFLOW))
  { cerr << "Error: Detected overflow." << endl; failedtest = true; }
if (std::fetestexcept(FE_UNDERFLOW))
  { cerr << "Error: Detected underflow." << endl; }
if (failedtest) { std::abort(); } 
  #endif
#endif
    return 0;
}

extern "C"  {
  void ad_boundf(int i)
  {
    /* so we can stop here */
    exit(i);
  }
}

#!/bin/bash

#Compilation
admb apecosm_size.tpl

project='MALASPINA' #'MALASPINA' #'MIXED'
zone='all' # 'Nomz' or 'omz' or 'all'
MC=0
#sed -i "14s/.*/$zone/" apecosm.dat
if [ $zone = 'all' ];then
	nb_site_MALASPINA=123
	nb_site_IMOS=316
	nb_site_PIRATA=162
	let "nb_site_MIXED=$nb_site_MALASPINA + $nb_site_IMOS + $nb_site_PIRATA"
elif [ $zone = 'Nomz' ];then
	nb_site_MALASPINA=0
	nb_site_IMOS=0
	nb_site_PIRATA=0
elif [ $zone = 'omz' ];then
	nb_site_MALASPINA=0
	nb_site_IMOS=0
	nb_site_PIRATA=0
fi

nb_site_t_MALASPINA=124
nb_site_t_IMOS=739
nb_site_t_PIRATA=167
nb_site_t_MIXED=$nb_site_MIXED

#Incrément pour la première boucle while

#Ce tableau contient les numéros des lignes dans le fichier bound_param_epi.txt pour chaque paramètre à modifier sauf la première valeur qui ne sert à rien (mais qui doit être gardée)
tab_pos_param=('0' '3' '11' '2' '10' '7' '15' '6' '14')
tab_pos_phase_adv_dif=('0' '20' '28' '24' '32') #adv2 diff2 adv3 diff3

len_pos_param=${#tab_pos_param[*]}
len_pos_phase=${#tab_pos_phase_adv_dif[*]}

#Les noms des paramètres calibrés pour les épi
variables_epi=('SIGM_TCOR0' 'SIGM_LIGHT1' 'OPT_LIGHT1' 'ADVz1' 'DIFFz1' 'DzPHY')
#La position de chaque paramètre (numéro de ligne) dans le fichier .dat (apecosm.dat)
position_epi=('26' '28' '30' '32' '34' '20' )

#récupérer la taille du tableau:
len_var_epi=${#position_epi[*]}
let "len_epi=$len_var_epi - 1"


var_tab=('cluster_list') # 'DL') #'alpha1' 'alpha3') # 'oxy_min' 'par_attenuation')
len_var_tab=${#var_tab[*]}
let "len_var_tab= $len_var_tab - 1"

#pathway2="/home/belharet/Bureau/Admb/admb_apecosm/new_version/migrants/data/MALASPINA/"
pathway="/media/belharet/HD_belharet/Optimization_admb/data/$project/"

if [ $MC = 1 ]
then
	iteration_nb=1 #100
	#let "nb_site=${nb_site_$project}"
else
	iteration_nb=1
fi

ind=1

echo "iteration_nb = $iteration_nb "
#----------------------------------------------------------------------------------------------------------------
# Supprimer le fichier apecosm_size.std s'il existe
while [ $ind -le $iteration_nb ];do

	#Si le fichier apecosm.std existe, on le supprime
if [ -e "apecosm_size.std"  ]
then
        rm apecosm_size.std
fi

#----------------------------------------------------------------------------
for i in `seq 0 $len_var_tab`; do

	filename="${pathway}${var_tab[$i]}_selected_bis.txt"
	#Si le fichier $filename existe, on le supprime
	if [ -e $filename  ]
	then
        	rm $filename
	fi
	# On crée le fichier filename
	touch $filename
	echo "#" >> $filename
done


#--------------------------------------------------------------------------------------------	

if [ $MC = 1 ]
then
	#Créer la liste aléatoire de 200 profiles (40omz + 160 Nomz)

	nombre_max1=770 #270
	nombre_max2=46
	nombre_nb_1=400  #le nombre total de sites à utiliser pour la calibration
	nombre_nb_2=400

	let "nb_site_$project = $nombre_nb_1 + $nombre_nb_2"
        
	#sélection aléatoire des sites Nomz
	id=1   #initialise
	while [ $id -le $nombre_nb_1 ]
	do
  	nombre1=$RANDOM
  	let "nombre1 %= $nombre_max1"  # Ramène $nombre dans l'intervalle ]1 $nombre_max[. Puis ajouter 1 pour éviter la ligne qui commence par # dans les fichiers
  	let "nombre1 = nombre1 + 1 + 1" # Ramène $nombre dans l'intervalle [1 $nombre_max]. Puis ajouter 1 pour éviter la ligne qui commence par # dans les fichiers
  	#extraire la ligne $nombre des fichiers et modifier les nouveaux fichiers
  	for var in `seq 0 $len_var_tab`; do
  		line1=`sed -n $nombre1'p' "${pathway}${var_tab[$var]}_Nomz.txt"`
  		echo $line1 >> "${pathway}${var_tab[$var]}_selected_bis.txt"
  	done

	 let "id = $id + 1" 
	done

        # sélection aléatoire des sites omz 
	id=1   #initialise

	while [ $id -le $nombre_nb_2 ]
        do
        nombre2=$RANDOM
        let "nombre2 %= $nombre_max2"
        let "nombre2 = nombre2 + 1 + 1"
        #extraire la ligne $nombre des fichiers et modifier les nouveaux fichiers
        for var in `seq 0 $len_var_tab`; do
                line2=`sed -n $nombre2'p' "${pathway}${var_tab[$var]}_omz.txt"`
                echo $line2 >> "${pathway}${var_tab[$var]}_selected_bis.txt"
        done

         let "id = $id + 1"
        done

else

 for var in `seq 0 $len_var_tab`; do
	 if [ $zone = 'all' ];
	 then 
 		#sed -n '2,$p' "${pathway}${var_tab[$var]}_Nomz.txt" >> "${pathway}${var_tab[$var]}_selected_bis.txt"
 		#sed -n '2,$p' "${pathway}${var_tab[$var]}_omz.txt" >> "${pathway}${var_tab[$var]}_selected_bis.txt"
		sed -n '2,$p' "${pathway}${var_tab[$var]}_selected.txt" >> "${pathway}${var_tab[$var]}_selected_bis.txt"

	else
		sed -n '2,$p' "${pathway}${var_tab[$var]}_$zone.txt" >> "${pathway}${var_tab[$var]}_selected_bis.txt"
	fi	
 done


fi
# indiquer le nombre de sites à utiliser pour la calibration dans le fichier .dat
sed -i "4s/.*/$project/" apecosm_size.dat

let "var_int=nb_site_$project"
sed -i "6s/.*/$var_int/" apecosm_size.dat

sed -i "10s/.*/$zone/" apecosm_size.dat

let "var_int=nb_site_t_$project"
sed -i "36s/.*/$var_int/" apecosm_size.dat

#----------------------------------------------------------------------------------------------------------
#Extraire les paramètres des épipélagiques

#	for j in `seq 0 $len_epi`;do
#		let "toto=$j+2"
#		#extraire la ligne $toto du fichier "param_$var.txt"
#	       	line1=`sed -n $toto'p' ../epipelagics/outputs/$project/param_bis.txt`
#	        #extraire la partie 3 de cette ligne (qui contient la valeur du paramètre)	
#		param1=`echo $line1 | cut -d' ' -f3`
#		#récupérer la valeur se trouvant à la ligne ${pos[$j]} du fichier "initial_parameters.txt"
#		sed -i "${position_epi[$j]}s/.*/$param1/" apecosm_size.dat
#		
#		#param0=`sed -n ${position_epi[$j]}'p' initial_parameters.txt`
#		#remplacer par la nouvelle valeur
#		#sed -i "${position_epi[$j]}s/$param0/$param1/" initial_parameters.txt

#	done
#-----------------------------------------------------------------------------------------------------------
	
	./apecosm_size -nox

#-----------------------------------------------------------------------------------------------------------

	#Vérifier si le fichier apecosm.std existe  
	if [ -e $"apecosm_size.std"  ]
	then
		cp apecosm_size.std outputs/$project/$zone/param_${zone}_$ind.txt
		mv "${pathway}cluster_list_selected_bis.txt" outputs/$project/$zone/cluster_list_$ind.txt
		echo "iteration $ind effectuée"
		#mettre à jour ind
		let "ind += 1"
	fi

	if [ $MC = 0 ]
	then
  		let "ind += 1"
	fi

done # while iteration

echo 'Fin du programme'

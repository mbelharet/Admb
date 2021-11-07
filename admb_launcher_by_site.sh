#!/bin/bash

#Compilation
admb apecosm_size.tpl

project='MALASPINA' #'IMOS' #'MALASPINA' #'MIXED'
zone='all' # 'Nomz' or 'omz' or 'all'
MC=0
#sed -i "14s/.*/$zone/" apecosm.dat
if [ $zone = 'all' ];then
	nb_site_MALASPINA=1
	nb_site_IMOS=228
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
nb_site_t_IMOS=228
nb_site_t_PIRATA=167
nb_site_t_MIXED=$nb_site_MIXED

#Incrément pour la première boucle while

var_tab=('cluster_list') # 'DL') #'alpha1' 'alpha3') # 'oxy_min' 'par_attenuation')
len_var_tab=${#var_tab[*]}
let "len_var_tab= $len_var_tab - 1"

pathway="/media/belharet/HD_belharet/Optimization_admb/data/$project/"

iteration_nb=123

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
# Créer la liste des sites

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


 for var in `seq 0 $len_var_tab`; do
	 if [ $zone = 'all' ];
	 then 
		sed -n '${ind},${ind}p' "${pathway}${var_tab[$var]}_selected.txt" >> "${pathway}${var_tab[$var]}_selected_bis.txt"

	else
		sed -n '2,$p' "${pathway}${var_tab[$var]}_$zone.txt" >> "${pathway}${var_tab[$var]}_selected_bis.txt"
	fi	
 done


# indiquer le nombre de sites à utiliser pour la calibration dans le fichier .dat
sed -i "4s/.*/$project/" apecosm_size.dat

let "var_int=nb_site_$project"
sed -i "6s/.*/$var_int/" apecosm_size.dat

sed -i "10s/.*/$zone/" apecosm_size.dat

let "var_int=nb_site_t_$project"
sed -i "36s/.*/$var_int/" apecosm_size.dat

#----------------------------------------------------------------------------------------------------------
	
	./apecosm_size -nox

#-----------------------------------------------------------------------------------------------------------

	#Vérifier si le fichier apecosm.std existe  
	if [ -e $"apecosm_size.std"  ]
	then
		cp apecosm_size.std outputs/$project/$zone/param_${zone}_${ind}_size.txt
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

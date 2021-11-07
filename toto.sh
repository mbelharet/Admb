#!/bin/bash

pathway='/media/belharet/HD_belharet/Optimization_admb/data/IMOS/'
vars=('oxy' 'par')
let "var_len=${#vars[*]} -1"
for j in `seq 0 $var_len`; do
	var="${pathway}${vars[$j]}"
	for i in `seq 1 228`; do
		 mv ${var}_$i.txt ${var}_d_$i.txt
		cp ${var}_d_$i.txt ${var}_n_$i.txt
	done
	echo "La variable " $var " a été traitée !"
done

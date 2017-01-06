#!/bin/bash

for redshift in 1.7 1.8 1.9 2.0 2.1 2.2 2.3 2.4 2.5 2.6 2.7 2.8 2.9 3.0 

do
	for number in 1100 1200 1300 1400 1500 1600 1700 1800 1900

	do
		head -"${number}" SB2_B2004a_"${redshift}"z_Mags.txt > SB2_B2004a_"${redshift}"z_Mags_"${number}".txt
	done

done


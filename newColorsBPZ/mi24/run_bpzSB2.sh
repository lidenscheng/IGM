#!/bin/bash

	/software/lsstlib/Import/enthoughtPython/epd-7.3-2-rh5-x86_64/bin/python /home/lidenscheng/bpz-1.99.3/bpz.py meanTrans_1YrErrors/meanIGM_SB2_B2004a_1.7z_Mags.txt -COLUMNS meanIGM.columns -FILTER_DIR ~/MK_DirectSim/filters/ -SED_DIR ~/MK_DirectSim/SEDs/ -SPECTRA SB2.list -PRIOR none -MEAN_IGM yes -MADAU no -NEW_AB yes 

#  	/software/lsstlib/Import/enthoughtPython/epd-7.3-2-rh5-x86_64/bin/python /home/lidenscheng/bpz-1.99.3/bpz.py LOS/SB2_B2004a_1.7z_Mags.txt -COLUMNS losNoErrors.columns -FILTER_DIR ~/MK_DirectSim/filters/ -SED_DIR ~/MK_DirectSim/SEDs/ -SPECTRA SB2.list -PRIOR none -MEAN_IGM yes -MADAU no -NEW_AB yes

for redshift in 1.8 1.9 2.0 2.1 2.2 2.3 2.4 2.5 2.6 2.7 2.8 2.9 3.0 

do

	/software/lsstlib/Import/enthoughtPython/epd-7.3-2-rh5-x86_64/bin/python /home/lidenscheng/bpz-1.99.3/bpz.py meanTrans_1YrErrors/meanIGM_SB2_B2004a_"${redshift}"z_Mags.txt -COLUMNS meanIGM.columns -FILTER_DIR ~/MK_DirectSim/filters/ -SED_DIR ~/MK_DirectSim/SEDs/ -SPECTRA SB2.list -PRIOR none -MEAN_IGM yes -MADAU no

#  	/software/lsstlib/Import/enthoughtPython/epd-7.3-2-rh5-x86_64/bin/python /home/lidenscheng/bpz-1.99.3/bpz.py LOS/SB2_B2004a_"${redshift}"z_Mags.txt -COLUMNS losNoErrors.columns -FILTER_DIR ~/MK_DirectSim/filters/ -SED_DIR ~/MK_DirectSim/SEDs/ -SPECTRA SB2.list -PRIOR none -MEAN_IGM yes -MADAU no

done 

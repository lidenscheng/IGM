//calculate average and std of IGM transmission
//first calculated to see what number of LOS is good enough
//decided to go with 9000 LOS
//created separate files for mean transmissions over 9000LOS

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <typeinfo>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

using namespace std;

int main(int narg, char* arg[])
{

  double zval;
  int LoS; 
//  int multi=0;

  //--- decoding command line arguments 
//  cout << " decoding command line arguments ..."<<endl;
  char c;

  while((c = getopt(narg,arg,"z:mh")) != -1) 
    {
      switch (c) 
	{
	case 'z' :
	  sscanf(optarg,"%lf",&zval);
	  break;
	case 'm' : // read in multiple files
//	  sscanf(optarg,"%lf",&zval);
	  zval= atof(arg[2]);
	  LoS= atof(arg[3]); 
//	  multi = 1;
	  cout << "Reading in multiple files." << endl;
	  break;
	case 'h' :
	default :
	  cout << "read_transmission -z <redshift> [-m]" << endl;
	  return -1;
	}
    }


  //  string transFileName_pre = "/home/matthewkirby/DirectSim/testfiles/LineOfSightTransmissionData/Transmission_";
  
//string transFileName_pre = "/raid00/elliott/IGM/DirectSim/testfiles/Transmission_";
//string transFileName_pre = "Transmission_";

// string transFileName_pre = "/home/lidenscheng/MK_DirectSim/newTransmissions/";

string transFileName_pre = "/raid00/lidenscheng/Transmissions/";

 stringstream ss_z, ss_LoS; 
 ss_z << zval;
 ss_LoS << LoS;  

 ofstream output;

//1st outputName for stats subdirectory, 2nd is for mean transmissions over 9000 LOS files 
// string outputName=  "/home/lidenscheng/MK_DirectSim/newTransmissions/stats/" + ss_z.str()+ "z_" + ss_LoS.str() + "_linesOfSight.txt"; 
 string outputName=  "/raid00/lidenscheng/Transmissions/meanTransmissions/" + ss_z.str()+ "z_9000LOS_meanTransmissons.txt";   
 output.open(outputName.c_str(), ofstream::out);


//  int numberFiles = 1;
//  int iFile= 1; 
//  if (multi) nFiles = 12;

//  int maxLOS= 750; 

//  int maxLambda= ((100+ 1250*(1+zval))-3000)/0.1; 	  

  int numberOfLines= 1+(((100+ 1250*(1+zval))-3000)/0.1);   //number of lines in a line of sight file for a particular z, works for z ending in 0.05 or 0.0

//  int sizeOfArrays= LoS*numberOfLines; 

   double wavelengths[numberOfLines]; 
   double transmissions[numberOfLines]; 
   double sums[numberOfLines]; 
   double averages[numberOfLines]; 
   double std[numberOfLines]; 
   double sumsOfSquares[numberOfLines]; 

   int counter;

   double wavelength=0.0, transmission=0.0; 

   for(int i=1; i<= LoS; i++) 
   {
	counter= 0; 
	stringstream ss_i; 
	ss_i << i;
	string transFileName= transFileName_pre + ss_z.str() + "z/" + ss_z.str() + "z_LineOfSight_" + ss_i.str() + ".txt"; 

        ifstream transmissionData;
        transmissionData.open(transFileName.c_str(), ios::in);

    	if (!transmissionData.is_open()){
      		cout << "Unable to open file: " << transFileName << endl;
      		return 1;
    	}

    	while(!transmissionData.eof())
	{
	
			transmissionData >> wavelength >> transmission; 
			wavelengths[counter] = wavelength;
//			transmissions[counter] = transmission;
			sums[counter] += transmission; 
			counter++;
	}
	

	transmissionData.close();
 
    }

	
   for(int j=0; j<numberOfLines; j++)
   {
	averages[j]= sums[j]/LoS; 
	
   }

/*	
   for(int i=1; i<= LoS; i++) 
   {
	counter= 0; 
	stringstream ss_i; 
	ss_i << i;
	string transFileName= transFileName_pre + ss_z.str() + "z/" + ss_z.str() + "z_LineOfSight_" + ss_i.str() + ".txt"; 

        ifstream transmissionData;
        transmissionData.open(transFileName.c_str(), ios::in);

    	if (!transmissionData.is_open()){
      		cout << "Unable to open file: " << transFileName << endl;
      		return 1;
    	}

    	while(!transmissionData.eof())
	{
	
			transmissionData >> wavelength >> transmission; 
			sumsOfSquares[counter] += (transmission - averages[counter])*(transmission - averages[counter]);
			counter++;
	}
	

	transmissionData.close();
 
    }
*/


//printing only average transmissions for separate mean transmission files 
//uncomment above section to print to mean and std files in stats subdirectory 
   for(int j=0; j<numberOfLines; j++)
   {
//	std[j] = sqrt(sumsOfSquares[j]/LoS);
	
//	output << wavelengths[j]*1.0E10 << "\t" << averages[j] << "\t" << std[j] << endl; 
        output << wavelengths[j] << "\t" << averages[j] << endl;


	
   }



   output.close();
   return 0;

}


//program to read in the binary transmission files and output them to text files
//12 binary files for each zsource, 750 lines of sight in each file 
//9,000 lines of sight in total for each zsource 
//creates 9,000 text files, one for each line of sight 
// first column is wavelength in angstroms, second column is transmission 

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
  int multi=0;

  //--- decoding command line arguments 
  cout << " decoding command line arguments ..."<<endl;
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
	  multi = 1;
	  cout << "Reading in multiple files." << endl;
	  break;
	case 'h' :
	default :
	  cout << "read_transmission -z <redshift> [-m]" << endl;
	  return -1;
	}
    }


  //  string transFileName_pre = "/home/matthewkirby/DirectSim/testfiles/LineOfSightTransmissionData/Transmission_";
  
string transFileName_pre = "/raid00/elliott/IGM/DirectSim/testfiles_DLA/Transmission_";
//string transFileName_pre = "Transmission_";

  int nFiles = 1;
  if (multi) nFiles = 12;
  int counter=1; 

  // Loop over files
  for (int iFile=1; iFile<=nFiles; iFile++) {

    stringstream ss_z, ss_seq;
    ss_z << zval;
    if (multi) 
      ss_seq << "_" << iFile << ".dat";
    else
      ss_seq << ".dat";
    
    string transFileName_pst = "zSource_750nLos_40LynMax" + ss_seq.str();
    
    string transFileName = transFileName_pre + ss_z.str() + transFileName_pst;
    int nLoS;                                       //The number of lines of sight to examine for each source redshift
    double zSource;                                 //Starting redshift of the background source
    string line;

    
    // open input file
    ifstream transmissionData;
    transmissionData.open(transFileName.c_str(), ios::in | ios::binary);
    if (!transmissionData.is_open()){
      cout << "Unable to open file: " << transFileName << endl;
      return 1;
    }
    
    cout << "Opened transmission file: " << transFileName << endl;
    
    // Get redshift
    transmissionData.read((char*)&zSource, sizeof(double));
    
    // Get nLoS
    transmissionData.read((char*)&nLoS, sizeof(int));

	cout << zSource << "	" << nLoS << endl; 
    
    
    // Get the wavelength data
    double wavelength=0;
    vector<double> wavelengths; 
  
//       string wavelengthData= "wavelength.dat"; 
//       ofstream outputWavelength;
//       outputWavelength.open(wavelengthData.c_str(), ofstream::out);

    while (wavelength>=0) {
      transmissionData.read((char*)&wavelength, sizeof(double));

//      outputWavelength << wavelength << endl; 

      if (wavelength>0)  wavelengths.push_back(wavelength);

//      outputWavelength << wavelength << endl; 
    }
    
//    for(int i=0; i < wavelengths.size(); i++)
//	{
//    		cout << wavelengths[i] << endl; 
//	}
    
    cout << "n Wavelengths: " << wavelengths.size() << endl;

//    nMod = wavelengths.size()/maxHist;
   
    // Loop over the lines of sight
    double transmission;
    vector<double> transmissions;


    for (int iLoS=0; iLoS<nLoS; iLoS++) {
      
      // for each line of sight we need to read out transmission at each wavelength
      transmission = 0;
//      ihist = 0;
//      int nWave = 0;
	
       stringstream ss_los, ss_file; 
       ss_los << counter; 
       ss_file << iFile; 

//       string lineOfSight_pre= "./separateFiles/"; 
//       string lineOfSightData= "./test/transmissionFile" + ss_z.str()+ "zSource_LineOfSight" + ss_los.str() + ".dat"; 

       string lineOfSight_pre= "/raid00/lidenscheng/Transmissions/"; 
       string lineOfSightData= lineOfSight_pre + ss_z.str()+ "z/" + ss_z.str() + "z_LineOfSight_" + ss_los.str() + ".txt"; 

       ofstream output;
       output.open(lineOfSightData.c_str(), ofstream::out);

     
//      if (iLoS%25 == 0 && iLoS > 0) 
//	cout << "Reading iLoS: " << iLoS << endl;

      
      while (transmission > -1) {
	transmissionData.read((char*)&transmission, sizeof(double));

//	output << wavelength << "	" << transmission << endl; 
//	output << transmission << endl; 
	
	// See that we're not at the end of this set
	if (transmission > -1) {

		transmissions.push_back(transmission);


	}
//	nWave++;
      } // end of transmission data
  

//	cout << iLoS << "	" << wavelengths.size() << "	" << transmissions.size() << endl;   

    for(int j=0; j < transmissions.size(); j++)
//    for(int j=0; j < wavelengths.size(); j++)

	{

    		output << wavelengths[j] <<"	" << transmissions[j] << endl; 
//    		output << transmissions[j] << endl; 
//    		output << wavelengths[j] << endl; 
	}


/*    for(int j=0; j < wavelengths.size(); j++)
                output << wavelengths[j]  << endl;


    for(int k=0; k < transmissions.size(); k++)

        {
                output << transmissions[k] << endl;
        }

*/

//	cout << "line of sight " << iLoS << endl;

//	cout << iLoS << "	" << wavelengths.size() << "	" << transmissions.size() << endl;   
    
	counter++; 
	transmissions.clear(); 
//	transmissions.erase (transmissions.begin(),transmissions.end()); 

	output.close(); 

    } // end of lines of sight

    
    transmissionData.close();
    wavelengths.clear();

//    wavelengths.erase (wavelengths.begin(),wavelengths.end()); 

  }    // End of loop over files
  

	return 0;
};



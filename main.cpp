


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include "config.h"
#include "meta.h"

using namespace std; 

void output(Config& ConfigFile, Meta& MetaFile);


int main(int ac, char * arg[]) 
   	 {
     char * fileName (arg[1]);
     char * fileExt = strrchr(fileName, '.');
     char configExt [] = ".conf";
     char metaExt [] = ".mdf";
     string metaFile;
     string errorMessage;
     int found;

     
     if(strcmp(fileExt,configExt) == 0)
     {
       Config ConfigFile(fileName);
       metaFile = ConfigFile.GetMetaFile();
       found = metaFile.find(metaExt);
       if((found != string::npos) && (!ConfigFile.getBadData()))
       {
       	
         Meta MetaFile(metaFile, ConfigFile);
          
         output(ConfigFile, MetaFile);
         
       }
       else
       {
       	errorMessage = "Meta File Extension isnt right ";
       }
       
     }
     else
     {
     	cout << configExt <<endl;
     	cout << fileExt <<endl;
     	cout << "Config File extension isn't right" << endl;
     }
      cout <<"About to finish the program" <<endl;
      
     return 0;
   }


//Outputs the data from the two files 

void output(Config &ConfigFile, Meta &MetaFile)
{
 
  fstream OutPut;
  
  string DataFile;

  if(ConfigFile.GetFile())
  {

   DataFile = ConfigFile.Getoutput();	
   OutPut.open(DataFile.c_str(), ios::out);

  if(OutPut.good())
   {

   	//ConfigFile.output(OutPut);
   	if(!ConfigFile.getBadData())
   	{
   		
   		MetaFile.output(OutPut);
   	}
   
   	 OutPut.close();
   }
 }

}

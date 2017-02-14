#ifndef META_H
#define META_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "metadata.h"
#include "config.h"

using namespace std;

// What the heck is PCB states do I create them myself or use pid_t
// combine all of the data types into my h file for convienence 
// delete the config output 
// correct the total time so that it does it in the parsing

class Meta
   {
      public:
      	Meta(string fileName, Config configObj);
      	~Meta();

      	void MetaOpenFile();
      	void MetaCloseFile();
      	void MetaGetData();
      	string GetDescriptor(char objectName,string line,  int position);  
      	int GetNumber(string line, int position);
         int SkipWhiteSpace (string line, unsigned index);
         int FindChar (string line, int positon, char item);
         void GetTotalTime();
         void output(fstream &File);
         char GetIDChar(string line, int position);
         int FindLeftPar(string line, int position);
         int updateIndex(string line, int position);
         // allocate memory
         // I/O thread create
         //start Time
         // End time
         // post Time 
         // get ID
         //runTime
         

      	

      private:
      	bool  metaEnd, metaEmpty, metaBadData, metaClosed;
      	string error, meta;
      	fstream metaFile;
         Config ConfigObj;
      	//char * config;
      	vector <MetaData> items; // should I make this a pointer?????
     


   };


#endif
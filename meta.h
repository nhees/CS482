#ifndef META_H
#define META_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime.h>
#include <queue>
#include "metadata.h"
#include "config.h"

using namespace std;

// What the heck is PCB states do I create them myself or use pid_t
// combine all of the data types into my h file for convienence 
// delete the config output 
// correct the total time so that it does it in the parsing

enum STATE
         {
            START, READY, RUNNING, WAITING, EXIT
         };

struct PCB
   {
     STATE CURRENT;
   };



class Meta
   {
      public:
      	Meta(string fileName, Config configObj);
      	~Meta();

      	void MetaOpenFile();
      	void MetaCloseFile();
      	bool MetaGetData();
      	string GetDescriptor(char objectName,string line,  int position);  
      	int GetNumber(string line, int position);
         int SkipWhiteSpace (string line, unsigned index);
         int FindChar (string line, int positon, char item);
         void GetTotalTime();
         void output(fstream &File);
         char GetIDChar(string line, int position);
         int FindLeftPar(string line, int position);
         int updateIndex(string line, int position);
         void StartTime();
         // allocate memory
         // I/O thread create
         //start Time
         // End time
         // post Time 
         // get ID
         //runTime
         //thread run time
         
       

      	

      private:
      	bool  metaEnd, metaEmpty, metaBadData, metaClosed;
         clock_t currTime, startTime;
      	string error, meta;
      	fstream metaFile;
         Config ConfigObj;
         PCB PCBSTATE;      	//char * config;
      	vector <MetaData> items; // should I make this a pointer?????
         queue <MetaData> operations;
         queue <string> OutPut;
     


   };

  


#endif
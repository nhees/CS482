#ifndef META_H
#define META_H

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
//#include <mutex>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <queue>
#include "metadata.h"
#include "config.h"

using namespace std;



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
         float GetTotalTime(MetaData operation);
         void output(fstream &File);
         char GetIDChar(string line, int position);
         int FindLeftPar(string line, int position);
         int updateIndex(string line, int position);
         void StartTimer();
         void PostTime(string Message);
         void OperationProcess(MetaData Process);
         //Provided to students from TA Vineeth
         unsigned int allocateMemory( int totMem );
         
         
         void * ThreadLaunch(void * time);
        
         // I/O thread create
         // End time
         // post Time 
         // get ID
         
         //thread run time
         
       

      	

      private:
      	bool  metaEnd, metaEmpty, metaBadData, metaClosed;
         int processCount, memoryCall,memorySize, PrinterCount, PrinterLimit, HardCount, HardLimit;
         clock_t currTime, startTime;
      	string error, meta;
      	fstream metaFile;
         Config ConfigObj;
         PCB PCBSTATE;      	//char * config;
      	vector <MetaData> items; // should I make this a pointer?????
         queue <MetaData> operations;
         queue <string> OutPutFile, OutPutMon;
         //pthread_mutex_t locker;


   };

  void RunTimer(float time);
  void *ThreadTimer(void* time);
 


#endif
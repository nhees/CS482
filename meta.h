#ifndef META_H
#define META_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "metadata.h"
#include "config.h"

using namespace std;

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
         

      	

      private:
      	bool  metaEnd, metaEmpty, metaBadData, metaClosed;
      	string error, meta;
      	fstream metaFile;
         Config ConfigObj;
      	//char * config;
      	vector <MetaData> items; // should I make this a pointer?????
     


   };


#endif



#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "object.h"

using namespace std;

class Config
   {
      public:
      	Config(char * fileName);
      	Config (const Config &obj);
      	~Config();
 // OPEN META FILE 
      	void OpenFile();
      	void CloseFile();
      	void GetData();
      	void AddObject(string objectName); 
      	void GetLastWord(string firstword);
      	bool getBadData();
      	string GetMetaFile();
      	int GetTime(string ID);
      	void output(fstream &outputFile);
      	bool GetFile();
      	bool GetMonitor();

      	string Getoutput();   

      	friend class Meta;

      private:
      	bool monitor, fileStat, end, empty, badData, closed, folderBool;
      	string meta, error, outputStr, folder, log;
      	fstream file;
      	char * config;
      	vector <Object> computerList; 
     


   };


#endif
#ifndef CLASS_CONFIG_CPP
#define CLASS_CONFIG_CPP

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include "config.h"

using namespace std;

Config::Config(char *fileName)	
: monitor(false), fileStat(false), end(false), empty(true), badData(false),closed(false),config(fileName)
	{
	  
      OpenFile();
     
	}
Config ::Config(const Config &obj)   
 :monitor(obj.monitor), fileStat(obj.fileStat), end(obj.end), empty(obj.empty), badData(obj.badData), closed(obj.closed)
{
 
  
  for(auto it = obj.computerList.begin(); it != obj.computerList.end(); it++)
  {
    cout <<it->objectName <<endl;
    computerList.push_back(*it);
    
  }

}   	

Config::~Config()
	{
    while (!computerList.empty())
    {
      computerList.pop_back();
    }
		//DELETE DATA IN QUEUE
	}

      	
void Config::OpenFile()
	{
		
		string first;

		file.open(config, ios::in);
		if(file.fail())
		{
			error = "File wouldn't open";
			badData = true;
		}
		else 
		{
			cout << "File has been opened" << endl;
			while(!closed)
			{
			 
			 GetData();
			 
			}
      
		}

    
	}

void Config::CloseFile()
	{
		 
		file.close();
		closed = true;
		
	}
      	
// parses the config file 

void Config::GetData()
	{
		string temp, first, last;
	

		getline(file, first, ' '); 

       if(first == "Start") 
       {
       	empty = false;
       	getline(file, temp);
       }

       else if (first == "Version/Phase:")
       {
       	
        getline(file, temp);
        
       }
       else if (first == "File")
       {
       	 AddObject(first);
       	 

       }
       else if((first == "Processor")|| (first =="Monitor")||(first =="Hard")
       	|| (first =="Printer")|| (first =="Keyboard")||(first =="Memory")||(first =="Mouse")||(first =="Speaker"))
       {
       	
       	AddObject(first); 
       	
       }
       else if((first == "Log" )|| (first =="Log:"))
       {
       	AddObject(first);
        
       
       }
       else if (first == "End")
       {
         
       	 end = true;
         CloseFile();
       }
       else 
       {
         error = "Incorrect Component";
       	 badData = true;
         CloseFile();
       }


	}
      	
void Config::AddObject(string objectName)
    {
      GetLastWord(objectName);
    } 

void Config::GetLastWord(string firstWord)
   {
   	string data, temp, lastWord;
   	unsigned position;
    int time;
   	getline(file, data);
     
     position = data.rfind(' ');
 
     lastWord = data.substr(position + 1, data.size()); // adds +1 to position to get rid of the space
     temp = lastWord;
     
     if(firstWord == "File")
     {
      meta = lastWord;
     }
     else if (firstWord == "Log:" )
     {
       
     	 if (lastWord == "Both")
     	 {
         log = "Both";
         monitor = true;
         fileStat = true;
     	 }
     	else if(lastWord == "monitor")
     	 {
         log = "Monitor";
     	   monitor = true;
     	 }
     	else if(lastWord == "File")
     	 {
         log = "File";
         fileStat = true;
     	 }
       else
       {
        badData = true;
        error = "Incorrect Log Path";
       }

     
     }
     else if(firstWord == "Log")
     {
      //prevPos = position;
     	position = lastWord.find('/');
      
     	 if(position == string::npos)
     	 {
        
     		outputStr = lastWord;
     	 }
     	 else 
     	 {
        folder = temp;
        folderBool = true;
     		outputStr = lastWord.substr(position+1, lastWord.size());
     	 }
     }
     else   
      {
     	 
       if(firstWord == "Hard")
       {
        firstWord = "Hard drive";
       }
       time = stoi(lastWord, NULL, 10);
     	 Object tempObj(time, firstWord);
     	 computerList.push_back(tempObj); 
     	 cout <<"Object Data" << tempObj.cycleTime << " Name: " << tempObj.objectName << endl;
     	
     }
     

   }

      	
string Config::GetMetaFile()
	{
       return meta;
	} 

bool Config::getBadData()
{
  return badData;

}
bool Config::GetFile()
{
  return fileStat;
}
bool Config::GetMonitor()
{
  return monitor;
}

int Config::GetTime(string ID)
{
 
  auto it = computerList.begin();
  ID[0] = toupper(ID[0]);
  


  while(it->objectName != ID && it != computerList.end())
  {
    //cout <<"Iterator process " <<it->objectName <<endl;
    it++;
  }
  

  return it->cycleTime;
}      

string Config::Getoutput()
{
  
    return outputStr;
}


//output function for all of the config data
// it is passed the fstream and then outputted accordingly
void Config::output(fstream &File)
{
  if (fileStat)
   {
    File <<"Configuration File Data \n";
     if (empty)
     {
       File<<"Configuration file was empty \n";
     }
     else
     {
      for (auto it = computerList.begin(); it != computerList.end(); it++)
      {
        File << it->objectName << " = " << it->cycleTime <<" ms/cycle \n";
      }
      if(badData)
      {
        File << error <<"\n";
      }
      else
      {
        File <<"Logged to: " << log << " and " << outputStr <<"\n";
      }
     }
   }

   if(monitor)
   { 
     cout <<"Configuration File Data \n";
     if (empty)
      {
       cout <<"Configuration file was empty \n";
      }
     else
      {
       for (auto it = computerList.begin(); it != computerList.end(); it++)
       {
        cout << it->objectName << " = " << it->cycleTime <<" ms/cycle \n";
       }
     if(badData)
       {
        cout << error <<"\n";

       }
     else
      {
        cout <<"Logged to: " << log << " and " << outputStr <<"\n";
      }
     }

     
   }

    

}
#endif
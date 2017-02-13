#ifndef META_CPP
#define META_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "meta.h"

using namespace std;

//constructor
Meta::Meta(string fileName, Config configObj)
      :metaEnd(false), metaEmpty(true),metaBadData(false), metaClosed(false), meta(fileName), ConfigObj(configObj)
      {
       cout <<"In meta consturctor" <<endl;
       MetaOpenFile();
      
      }
//deconstructor      	
Meta::~Meta()
      {
            while (!items.empty())
                  {
                    items.pop_back();
                  }

      }

// opens the file and then calls getData and get total time
      // This is inorder to parse the data
void Meta::MetaOpenFile()
   {
      string first;

      metaFile.open(meta, ios::in);
      if(metaFile.fail())
      {
       error = "Meta file wouldn't open";
       metaBadData = true;
      }
      else
      {
       getline(metaFile, first, ' ');
       if(first == "Start")
       {
          MetaGetData();  
          GetTotalTime();
      
       }
       else 
        {
            metaEmpty = true;
            metaBadData = true;
            error= "Meta File is empty";
            MetaCloseFile();
        }
      }
   }
// closes the file
void Meta::MetaCloseFile() 
   {
     metaFile.close();
     metaClosed = true;
   }

      	
// Parses the meta Data document
void Meta::MetaGetData()
   {
     string line, process;
     char currChar,IDChar;
     int objNum;
     unsigned  endIndex, index = 0;

     getline(metaFile,line); //<-- Grabs the first line
    
       
       // grabs second line and proceeds to go through the rest of the document 
       getline(metaFile,line); 
      
       // This is only for the second line of the document because it should have start and Application

       currChar = line.at(index);
      // check for start
      if(currChar == 'S')
      {
         IDChar = currChar;   
            
         index++; 
         currChar = line.at(index);
         index = SkipWhiteSpace(line, index);
         if(currChar == '(')
         { 
            // Checks if it has the right descriptor
            process = GetDescriptor(IDChar, line , index+1);
            if(process == "Bad")
            {
                  
              error = "Incorrect description";
              metaBadData = true;
              MetaCloseFile();
            }
            else

            {     
                  // gets the number            
                  objNum = GetNumber(line, index); 
                  if(objNum >= 0)
                  {
                        index++;
                        currChar = line.at(index);
                        //Got S correct now checking if A is correct
                        while ((currChar != 'A' ) && ( currChar != '('))
                        {
                          
                         index++;
                         currChar = line.at(index);
                        }
                        
                        if(currChar == 'A')
                        {
                              
                              IDChar = currChar;
                              index = SkipWhiteSpace(line , index+1); //need to continue one   
                              currChar = line.at(index);
                              
                              if(currChar == '(')
                              {
                             
                                 process = GetDescriptor(IDChar,line, index+1);
                                 // index +1 so we can move past the (
                                 
                                    if (process != "Bad")
                                    {

                                          objNum = GetNumber(line, index);
                                          
                                          if (objNum >= 0)
                                          {
                                                 index = (line.find(')', index) +1);
                                            while (!metaClosed && !metaBadData) 
                                                {
                                                   
                                                  currChar = line.at(index);   // gets the next character
                                                  cout <<currChar <<endl;
                                                 
                                                  
                                                      /*OBJECTS*/
                                                if((currChar == 'P')||(currChar =='S')||(currChar == 'A')
                                                      ||(currChar =='I')||(currChar == 'O')||(currChar == 'M'))
                                                {
                                                      
                                                      IDChar = currChar;
                                                      index = line.find('(',index+1);
                                                    
                                                      if(index != string::npos)
                                                      {
                                                          // Gets the description
                                                         process = GetDescriptor(IDChar, line,index+1);
                                                         if(process != "Bad") 
                                                         {
                                                            
                                                            objNum = GetNumber(line, index);
                                                            index = (line.find(')', index) +1);
                                                            //checks if the number is valid
                                                            if(objNum>= 0)
                                                            {      //Checks if the program is ending
                                                                  if(IDChar == 'A')
                                                                  {
                                                                        if (process == "end")
                                                                        {
                                                                         endIndex = index;
                                                                         currChar = line.at(endIndex);

                                                                         while (endIndex <line.size() && currChar !='S' && currChar !='(')
                                                                         {
                                                                           endIndex++;
                                                                           currChar = line.at(endIndex);

                                                                         } 
                                                                         //checks if the Program is Ending via S
                                                                         if (currChar =='S')
                                                                         {
                                                                              endIndex = line.find('(',index+1);
                                                                              process = GetDescriptor(currChar,line, endIndex + 1);
                                                                              if(process == "end")
                                                                              {
                                                                                    metaEnd= true;
                                                                                    MetaCloseFile();
                                                                                    
                                                                              }
                                                                         }

                                                                        } 

                                                                  }
                                                                  else
                                                                  {
                                                                  MetaData data(objNum, process,IDChar, 0);
                                                                  //initalizes then pushes
                                                                  items.push_back(data);
                                                                  }

                                                            }
                                                            else
                                                            {
                                                             error = "Bad cycle number";
                                                             metaBadData = true;
                                                            }

                                                         }
                                                         else
                                                         {
                                                            error= "Bad description";
                                                            metaBadData = true;
                                                         }  
                                                      }
                                                      else
                                                      {
                                                           error = "No (";
                                                           metaBadData = true;
                                                      }
                                                      
                                                }
                                                else if(currChar == '(')
                                                {
                                                 metaBadData = true;
                                                 error ="No Meta id";
                                                 MetaCloseFile();

                                                }

                                                index++;

                                                 if (index == line.size()-1)
                                                      {  // at the end of the line needs to go to the next line 

                                                       getline(metaFile,line);
                                                       index = 0;
                                                    

                                                      } 
                                                } // while

                                          } // if A has all of the correct data
                                          else
                                          {
                                                metaBadData = true;
                                                error= "Incorrect cycle amount";
                                             // bad data function
                                          }
                                    }
                                    else
                                    {
                                          error = "incorrect description";
                                          metaBadData = true;

                                    }
                              }
                              else // no paraenthese
                              {
                                 error= "No paraenthese";
                                 metaBadData = true;
                                    // bad data function 
                              }


                        } 
                        else
                        {
                              error = "Incorrect Operator";
                              metaBadData = true;
                              MetaCloseFile();
                        }

                  }
              

            } // S process is correct
         }
      
     } // second line if

     else 
     {
      metaEmpty = true;
      MetaCloseFile();
     } // first operations isnt S

  
}
  
//Retrieve the description
//by going through the characters and then checking if valid      	
string Meta::GetDescriptor(char objectName, string line, int position)
   {
     char temp;
     string title;
     int index;


     index = SkipWhiteSpace(line, position);
     temp = line.at(index);

     while(temp!=')')
     {
       title.push_back(temp);
       index++;
       temp = line.at(index);
     }


     if(objectName == 'P')
     {
       if (title == "run")
       {
            return title;
       }
     }
     else if(objectName == 'S' || objectName == 'A')
     {
      if(title == "start" || title =="end")
      {
            return title;
      }
     }
     else if (objectName == 'I')
     {
      if(title == "hard drive" || title == "keyboard" || title == "mouse"||title =="monitor")
      {
            return title;
      }
     }
     else if (objectName == 'O')
     {
      if(title == "hard drive" || title == "monitor" || title == "speaker"||title == "printer")
      {
            return title;
      }
     }
     else if (objectName == 'M')
     {
      if(title == "block" || title == "allocate")
      {
            return title;
      }
     }

     return "Bad";
   }

//retrieves the cycles for the component      	
int Meta::GetNumber(string line, int position)
   {
     unsigned index = (line.find(')', position) +1);
     char temp;
     string num;
     temp = line.at(index);
    
     index = SkipWhiteSpace(line, index);
     temp = line.at(index);
    
     if(isdigit(temp) )
     {
       num.push_back(temp);
       index++;
      
       while (isdigit(temp) && index < line.size())
       {
           
         temp = line.at(index);
         num.push_back(temp);
         
         index++;
         
         
       }
      
       return stoi(num, NULL, 10);

     }
     else 
     {
      return -1;
     }

      
   }
//skips all of the white space
int Meta::SkipWhiteSpace (string line, unsigned index)
{
      char temp = line.at(index);

      while (temp == ' ' && index < line.size())
      {
            index ++;
            temp = line.at(index);
      }

      return index;


}

// Gets the total time for each meta component
void Meta::GetTotalTime()
{
     
      int cycleTime;

      for (auto it = items.begin(); it != items.end(); it++)
      {
            char ID = it->processID;
            if (ID == 'P')
            {
             cycleTime = ConfigObj.GetTime("Processor");
            }
            else if (ID == 'M')
            {
              cycleTime = ConfigObj.GetTime("Memory");
            }
            else if(ID =='I' || ID =='O')
            {
              cycleTime = ConfigObj.GetTime(it->descriptor);
              
            }

            it->time = it->cycles * cycleTime;

            

      }

}
int Meta::FindChar(string line, int position, char item) 
{
  return 0;
}



//outputs the meta data to the file and monitor
//when needed
// there is an error and it only outputs to monitor
// not sure why -_-
void Meta::output(fstream &Data)
{

 if(ConfigObj.fileStat)
 {

      Data <<"Meta-Data Metrics \n"; 
      cout <<"In the file if" <<endl;           
            if (metaEmpty)
            {
              Data <<"Meta File was Empty \n";
            }
          else
           {
             for (auto it = items.begin(); it != items.end(); it++)
               {
                  Data << it->processID << "(" << it->descriptor <<")" << it->cycles;
                  Data << " - " << it->time <<" ms \n";
               }
            if(metaBadData)
            {
             Data << error <<"\n";
            }
       
   }
   if(ConfigObj.monitor)
   {
      cout <<"Meta-Data Metrics" <<endl;
      for (auto it = items.begin(); it != items.end(); it++)
               {

                  cout << it->processID << "(" << it->descriptor <<")" << it->cycles;
                  cout << " - " << it->time <<" ms \n";
               }
            if(ConfigObj.badData)
            {
             cout << error <<"\n";
            } 
   }
 }
       

 
}

#endif
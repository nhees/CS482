#ifndef META_CPP
#define META_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include "meta.h"


using namespace std;

//constructor
Meta::Meta(string fileName, Config configObj)
      :metaEnd(false), metaEmpty(true),metaBadData(false), metaClosed(false),memoryCall(0),PrinterCount(0), 
      HardCount(0), meta(fileName), ConfigObj(configObj)
      {
       memorySize = ConfigObj.GetTime("MemorySize");
       HardLimit =ConfigObj.GetTime("Hard#");
       PrinterLimit = ConfigObj.GetTime("Printer#");
       //locker = PTHREAD_MUTEX_INITIALIZER;
       
       MetaOpenFile();
      
      }
//deconstructor      	
Meta::~Meta()
      {     // NEED TO EMPTY THE QUEUE
            while (!items.empty())
                  {
                    items.pop_back();
                  }

            while(!operations.empty())
            {
              operations.pop();
            }
//            scout <<"In meta deconstructor" <<endl;
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
          StartTimer();
          metaBadData = !MetaGetData();
         
      
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
   // First checks to make sure that the document starts with S(start) and A(start)
   // From there goes to collect the rest of the operations and add them into a queue.

bool Meta::MetaGetData()
   {
     string line, process;
     char currChar,IDChar;
     int objNum;//, processCount;
     unsigned  endIndex, index = 0;
      /*START TIME*/
     /*OUTPUT THE START*/

     getline(metaFile,line); //<-- Grabs the first line
    
       
       // grabs second line and proceeds to go through the rest of the document 
       getline(metaFile,line); 
      
       // This is only for the second line of the document because it should have start and Application

       currChar = GetIDChar(line, index);
      // check for start
       error = "File is Empty"; // Error message if the statement fails
      if(currChar == 'S')
      {
         PCBSTATE.CURRENT = START;
         metaEmpty = false;
         IDChar = currChar;   
            
       
         index = FindLeftPar(line, index + 1);
         error = "No Left Parenthese with operation"; // Error message if the statement fails
         if(index >=  0)
         { 
            // Checks if it has the right descriptor
            process = GetDescriptor(IDChar, line , index+1);
            error = "Incorrect Description given with operation"; // Error message if the statement fails

           if(process == "start")

            {        
                  objNum = GetNumber(line, index); 
                  error = "Object cycle amount is invalid"; // Error message if the statement fails

                  if(objNum >= 0) // checks if the number is valid
                  {
                            
                          currChar = GetIDChar(line, index);
                          error = "No Starting Process Operation"; // Error message if the statement fails

                        if(currChar == 'A')
                        {
                             
                            /*OUTPUT THE START OF PROCESS 1*/
                              
                              IDChar = currChar;
                              index = FindLeftPar(line, index+1);
                              error = "Left Parenthese isnt given with operation"; // Error message if the statement fails

                              if(index >= 0)
                              {
                                 currChar = line.at(index);
                                 process = GetDescriptor(IDChar,line, index+1);                               
                                    error = "No Starting Process Operation"; // Error message if the statement fails
                                  
                                   if (process == "start")
                                    {
                                          processCount  = 1; // First process
                                          objNum = GetNumber(line, index);
                                          error = "INVALID CYCLE AMOUNT"; // Error message if the statement fails 

                                          if (objNum >= 0)
                                          {
                                            MetaData dataA(objNum, process,IDChar, 0);
                                            operations.push(dataA);
                                            OperationProcess(dataA);
                                             /*IF THE PRGRAM STARTS WITH S(START) and A(START)*/
                                                

                                                 index = updateIndex(line, index); 
                                                
                                            while (!metaClosed && !metaBadData) 
                                                {

                                                 
                                                  currChar = GetIDChar(line, index);// line.at(index);  
                                               
                                                 if(currChar == 'E')
                                                 {
                                                  /*Found the end of the line moving to the next one*/
                                                  getline(metaFile,line);
                                                  index = 0;
                                                  currChar = GetIDChar(line,index);

                                                 }
                                                  
                                                      /*OBJECTS*/
                                                if((currChar == 'P')||(currChar =='S')||(currChar == 'A')
                                                      ||(currChar =='I')||(currChar == 'O')||(currChar == 'M'))
                                                {
                                                      // Valid command 
                                                      IDChar = currChar;
                                                      index = FindLeftPar(line, index);                                                    
                                                      error = "Left Parenthese isnt given with operation";

                                                      if(index != string::npos)
                                                      {
                                                          // Gets the description
                                                         process = GetDescriptor(IDChar, line,index+1);
                                                         error = "INCORRECT DESCRIPTION WITH OPERATION";

                                                         if(process != "Bad") 
                                                         {
                                                            
                                                            objNum = GetNumber(line, index);
                                                            index = updateIndex(line,index);
                                                            error = "INCORRECT CYCLE AMOUNT";
                                                            //checks if the number is valid
                                                            if(objNum>= 0)
                                                            {      /*CHECKS IF PROCESS IS ENDING*/
                                                               PCBSTATE.CURRENT = READY;
                                                                   if(IDChar == 'A')
                                                                     {
                                                                         if (process == "end")
                                                                          {
                                                                           endIndex = index;
                                                                           currChar = line.at(endIndex);

                                                                           endIndex = updateIndex(line, endIndex);
                                                                            MetaData dataB(objNum, process,IDChar, 0);
                                                                            operations.push(dataB);
                                                                            OperationProcess(dataB);

                                                                          //checks if the Program is Ending via S
                                                                             if (currChar =='S')
                                                                             {
                                                                              endIndex = FindLeftPar(line, index+1);
                                                                              process = GetDescriptor(currChar,line, endIndex + 1);
                                                                               if(process == "end")
                                                                                {
                                                                                    // return true ;

                                                                                    metaEnd= true;
                                                                                    MetaCloseFile();
                                                                                    return true;
                                                                                }
                                                                              }
                                                                              /*CHEKCING IF GETTING A NEW PROCESS*/
                                                                             else if(currChar == 'A')
                                                                              {
                                                                               index = FindLeftPar(line, index);
                                                                                process = GetDescriptor(currChar,line,index);
                                                                                 if(process == "Start")
                                                                                   {
                                                                                    processCount++;
                                                                                    index = updateIndex(line, index);
                                                                                    MetaData dataC(objNum, process,IDChar, 0);
                                                                                    operations.push(dataC);
                                                                                    OperationProcess(dataC);
                                                                                    PCBSTATE.CURRENT = EXIT;

                                                                                   }

                                                                              }

                                                                          } 

                                                                        }

                                                                  /*NOT THE A OPERATION*/
                                                                  else
                                                                  { /*ADDS OPERATION TO QUEUE*/
                                                                    MetaData data(objNum, process,IDChar, 0);
                                                                    data.time = GetTotalTime(data);
                                                                    items.push_back(data);
                                                                    operations.push(data); // LOADS To THE QUEUE
                                                                    OperationProcess(data);
                                                                    PCBSTATE.CURRENT = EXIT;
                                                                  }

                                                            }
                                                           
                                                      
                                                }
                                                else if(currChar == '(')
                                                {
                                                 
                                                 error ="No Meta id";
                                                 MetaCloseFile();
                                                 return false;

                                                }

                                            
                                                } // while

                                          } // if A has all of the correct data
                                        
                                    }
                                    
                              }
                              

                           }
                        } 
                       

                  }
              }

            } // S process is correct
         }
      
     } // second line if
     OutPutFile.push(error);
     return false; // SOMETHING WAS INCORRECT


  
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
float Meta::GetTotalTime(MetaData Operation)
{
  float cycleTime,cycleAmount = Operation.cycles;
  char ID = Operation.processID;


  string process;

  switch(ID)
  {
    case 'P':
    process = "Processor";
    break;

    case 'M':
    process = "Memory";
    break;

    default: // case 'I':// || 'O':
    process = Operation.descriptor;
   
  };

  cycleTime = (ConfigObj.GetTime(process)* .001);
  return (cycleTime * cycleAmount);//*.001);  // To put into milliSeconds 
    
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
  
//cout <<"In output" <<endl;
 if(ConfigObj.fileStat)
 {
  //cout <<"in file output" <<endl;
   while(!OutPutFile.empty())
   {
    
    Data << OutPutFile.front() << "\n";
    OutPutFile.pop();
   }

       
 }
 if(ConfigObj.monitor)
   {
    //cout <<"Monitor stuff" <<endl;
     while(!OutPutMon.empty())
     {
      cout << OutPutMon.front()<< endl;
      OutPutMon.pop();
     }
  
 }
       

 
}

char Meta::GetIDChar(string line, int position)
{
  
  int index = updateIndex( line,  position);
 
  if (index >= 0)
  {
    char current = line.at(index);
    return current;
  }

  
  return 'E';

}


int Meta::updateIndex (string line, int position)
{
 
  int  index = 0;
     index = position;
  int listLength = line.size() - 1;
   
  if(index >= 0) // Checking if given a valid input 
  {
    
  char current = line.at(position);
  while(current != 'A' && current != 'S' && current != 'P' && current != 'M' 
    && current != 'I' && current != 'O' && index != listLength)
  {
    index ++;
    current  = line.at(index);
    
  }
 
   if(index != listLength)
   {
    return index;
   }
  }
   
   return -1;

}

// Finds the left parenthese for the meta data when parsing
int Meta::FindLeftPar(string line, int position)
{
  int index = line.find('(',position);
  char current = line.at(index);
   if(current == '(')
   {
    return index;
   }
   return -1;
}

//Starts the clock on the program
void Meta::StartTimer()
{
  startTime = clock();
  PostTime("Simulator program starting");
}


void Meta::OperationProcess(MetaData Operation)
{

  char ID = Operation.processID;
  string allocate, description;
  stringstream message, process;
  int MemoryLocation;
 
  PCBSTATE.CURRENT = RUNNING;
  

  if (ID == 'A')
  {
    if (Operation.descriptor == "start")
    {
      
      PostTime(("OS: Starting Process" + processCount));
    }
    else
    {
      PostTime(("OS: Removing Process " + processCount));
    }
  }
  else if(ID == 'P')
  {
   

    message <<"Process "  <<processCount <<string(" : Start processing action");
   
    PostTime(message.str());

    message.str(string());
    message.clear();
    
    RunTimer(Operation.time);

    message << "Process " << processCount << string(" : End processing action");
    PostTime(message.str());

  }

  else if(ID == 'M')
  {
    message << "Process " << processCount << string(" : allocating memory");
    PostTime(message.str());
    MemoryLocation = ConfigObj.GetTime("System");
  
    RunTimer(Operation.time);
    MemoryLocation = allocateMemory(MemoryLocation);
    
    allocate = to_string(MemoryLocation);
    message.str(string());
    message.clear();
    message<<"Process " <<processCount << string (": memory allocated at 0X") <<allocate;
    PostTime(message.str());
    

  }
  else // OPERATION IS I/O
  {

    /*Need a thread for the operation*/
    pthread_t thread;
    if (Operation.descriptor  == "printer") 
    {
      if (PrinterLimit < PrinterCount)
      {
        PrinterCount = 0;
      }
      description = to_string(PrinterCount);
      message <<"Process " <<processCount << ": start PRNT " << description;
      PrinterCount ++;
    }       
    else if (Operation.descriptor == "hard drive")
    {
      if(HardLimit < HardCount)
      {
        HardCount = 0;
      }
      description = to_string(HardCount);
      message << "Process " <<processCount<< ": start HDD " << description;//Operation.descriptor = ("HDD " + HardCount);
      HardCount++;
    }
    else
    {
     message << "Process " << processCount << string(": start " + Operation.descriptor + " action");
    }
    PostTime(message.str());    
    //Thread work
   
    
    sem_init(&semaphore,0,0);
     pthread_create(&thread, NULL, ThreadTimer , &Operation.time); //(void *) &timeNum); //, (void *) timeNum); // FIX THE VOID * ISSUES
    
     pthread_join(thread, NULL);
  
     sem_destroy(&semaphore);
    // clears the sstring and posts the new message indicating the end of the action
   message.str(string());
   message.clear();
    message << "Process " << processCount << string(": end of action" );
    PostTime(message.str());
  }

}

void Meta::PostTime(string Message)
{
  
  PCBSTATE.CURRENT = WAITING;
  currTime = clock() - startTime;
  float time = ((float)currTime/CLOCKS_PER_SEC);
  
  string Time = to_string(time);  

 
  if(ConfigObj.fileStat)
  {
   OutPutFile.push(Time + " - " + Message);
  }
  if(ConfigObj.monitor)
  {
    OutPutMon.push(Time+ " - " + Message);
  }
}




unsigned int Meta::allocateMemory( int totMem )
{
  char * hex = new char [8]; 
  stringstream num;
  int address = memoryCall * memorySize; // get memory address
  memoryCall ++;

  if (totMem > address)
  {
    sprintf(hex,"%x",address);//itoa(address, hex, 16);
   
    num <<hex;
    num >>address;
  } 
  delete [] hex;
  return address;
    
}



void RunTimer(float time)
{
  time *= CLOCKS_PER_SEC;
  time += clock(); // Given current time add the extra time to it

  while (clock() < time) continue; 
}


void  *ThreadTimer(void * time)
{
  float timer = *((float*) time);
  RunTimer(timer);
  pthread_exit(NULL);

}


#endif

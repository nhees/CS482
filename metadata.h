
#include <iostream>
#include <string>

using namespace std;

#ifndef STRUCT_METADATA_H
#define STRUCT_METADATA_H


struct MetaData
   {
    MetaData(int cycles, string descriptor, char processID, float time);

    string descriptor; 
    char processID;
    int cycles;
    float time;
   };

#endif
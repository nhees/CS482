// struct with a string name and int 

#include <iostream>
#include <string>

using namespace std;

#ifndef STRUCT_LISTNODE_H
#define STRUCT_LISTNODE_H


struct Object
   {
    Object(int time, string name);

    string objectName;

    int cycleTime;
   };

#endif
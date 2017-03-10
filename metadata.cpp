#ifndef STRUCT_METADATA_CPP
#define STRUCT_METADATA_CPP

#include "metadata.h"


MetaData :: MetaData(int cycle, string descript, char ID, float totalTime)
	:descriptor(descript), processID(ID), cycles(cycle), time(totalTime)
 {
   
 }

 #endif
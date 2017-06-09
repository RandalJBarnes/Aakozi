//=============================================================================
// now.cpp
//
//    Return the current time and date as a character string.
//
// author:
//    Dr. Randal J. Barnes
//    Department of Civil, Environmental, and Geo- Engineering
//    University of Minnesota
//
// version:
//    09 June 2017
//=============================================================================
#include "now.h"

#include <ctime>
#include <string>

//-----------------------------------------------------------------------------
// Now
//
//    Return the current date and time as a string.
//-----------------------------------------------------------------------------
std::string Now()
{
   time_t rawtime;
   struct tm *timeinfo;

   time( &rawtime );
   timeinfo = localtime( &rawtime );

   std::string str( asctime(timeinfo) );
   str = str.substr(0, str.find('\n'));

   return str;
}

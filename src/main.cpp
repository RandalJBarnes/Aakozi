//=============================================================================
// main.cpp
//
//    The driver for the command line version of the user interface.
//
// author:
//    Dr. Randal J. Barnes
//    Department of Civil, Environmental, and Geo- Engineering
//    University of Minnesota
//
// version:
//    09 June 2017
//=============================================================================
#include <vector>
#include <set>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <time.h>

#include "engine.h"
#include "version.h"
#include "now.h"

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void Usage()
{
   std::cerr << std::endl;
   std::cerr << "Aakozi (" << Version() << ')'      << std::endl;
   std::cerr << "Usage: Aakozi <data filename> <buffer radius>" << std::endl;
   std::cerr << std::endl;
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void Banner( std::ostream& ost)
{
   ost << "================================================="  << std::endl;
   ost << "Aakozi                       (" << Version() << ')' << std::endl;
   ost << "================================================="  << std::endl;
}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   // Check the command line.
   if( argc != 3 )
   {
      Usage();
      return 1;
   }

   // Create a unique log filename using the system time.
   time_t now = time(0);
   struct tm t;
   localtime_s( &t, &now );

   const char *pattern = "Aakozi_%a_%d%b%y_%H%M%S.log";
   char logfilename[255];
   strftime(&logfilename[0], 255, pattern, &t);

   // Open the log file.
   std::ofstream logfile( logfilename );
   if( logfile.fail() )
   {
      std::cerr << "ERROR: could not open the log file <" << logfilename << "> for output.\n" << std::endl;
      Usage();
      return 1;
   }

   // Put the detailed header information out to the screen and to the logfile.
   Banner( std::cout );
   Banner( logfile );

   // Open the specified data file.
   std::ifstream datfile( argv[1] );
   if( datfile.fail() )
   {
      std::cerr << "ERROR: could not open the specified data file <" << argv[1] << "> for input." << std::endl;
      Usage();
      logfile.close();
      return 2;
   }

   // Get buffer radius.
   double radius = atof( argv[2] );
   if( radius <= 0.0 )
   {
      std::cerr << "ERROR: buffer radius = " << argv[2] << " is not valid;  0 < radius." << std::endl;
      std::cerr << std::endl;
      Usage();

      logfile.close();
      datfile.close();
      return 3;
   }

   // Put the run information out to the log file.
   logfile << "Run Date:   " << Now()   << std::endl;
   logfile << "Input file: " << argv[1] << std::endl;
   logfile << "Radius:     " << radius  << std::endl;

   // Read in the observation data from the specified datfile.
   std::vector<double> x;
   std::vector<double> y;
   std::vector<double> z;
   std::vector<int>  uid;

   std::string line;
   double xx, yy, zz;
   int id;

   logfile << std::endl;
   logfile << "OBSERVATIONS" << std::endl;
   logfile << "------------------------------------------------------\n";
   logfile << "  index   id           x           y           z      \n";
   logfile << "------------------------------------------------------\n";
   while( std::getline(datfile, line) )
   {
      std::istringstream is(line);
      if( is >> id >> xx >> yy >> zz )
      {
         uid.push_back(id);
         x.push_back(xx);
         y.push_back(yy);
         z.push_back(zz);
      }

      logfile << std::setw(5) << x.size();
      logfile << std::fixed << std::setw(12) << id;
      logfile << std::fixed << std::setw(12) << std::setprecision(2) << xx;
      logfile << std::fixed << std::setw(12) << std::setprecision(2) << yy;
      logfile << std::fixed << std::setw(12) << std::setprecision(2) << zz;
      logfile << std::endl;
   }
   logfile << "------------------------------------------------------\n";
   datfile.close();

   // Report the number of data.
   std::cout << std::endl << x.size() << " data read from <" << argv[1] << ">. \n";
   logfile   << std::endl << x.size() << " data read from <" << argv[1] << ">. \n";


/*
   // Identify and report the outliers.
   try
   {
      std::vector<Outlier> outliers;
      outliers = Aakozi_Engine(x,y,z,alpha);

      // Tabular output to the screen.
      std::cout << std::endl;
      std::cout << "IDENTIFIED OUTLIERS \n";
      std::cout << "-------------------------------------------------------------------------------\n";
      std::cout << "     #           x           y           z         uid        zhat      zscore \n";
      std::cout << "-------------------------------------------------------------------------------\n";

      for( std::vector<Outlier>::const_iterator it = outliers.begin(); it != outliers.end(); ++it )
      {
         int i = it->index;
         std::cout << std::setw(6) << i+1;
         std::cout << std::fixed << std::setw(12) << std::setprecision(2) << x[i];
         std::cout << std::fixed << std::setw(12) << std::setprecision(2) << y[i];
         std::cout << std::fixed << std::setw(12) << std::setprecision(2) << z[i];
         std::cout << std::fixed << std::setw(12) << uid[i];
         std::cout << std::fixed << std::setw(12) << std::setprecision(2) << it->zhat;
         std::cout << std::fixed << std::setw(12) << std::setprecision(2) << it->zscore;
         std::cout << std::endl;
      }
      std::cout << "-------------------------------------------------------------------------------\n";

      // Tabular output to the log file.
      logfile << std::endl;
      logfile << "IDENTIFIED OUTLIERS \n";
      logfile << "-------------------------------------------------------------------------------\n";
      logfile << "     #           x           y           z         uid        zhat      zscore \n";
      logfile << "-------------------------------------------------------------------------------\n";

      for( std::vector<Outlier>::const_iterator it = outliers.begin(); it != outliers.end(); ++it )
      {
         int i = it->index;
         logfile << std::setw(6) << i+1;
         logfile << std::fixed << std::setw(12) << std::setprecision(2) << x[i];
         logfile << std::fixed << std::setw(12) << std::setprecision(2) << y[i];
         logfile << std::fixed << std::setw(12) << std::setprecision(2) << z[i];
         logfile << std::fixed << std::setw(12) << uid[i];
         logfile << std::fixed << std::setw(12) << std::setprecision(2) << it->zhat;
         logfile << std::fixed << std::setw(12) << std::setprecision(2) << it->zscore;
         logfile << std::endl;
      }
      logfile << "-------------------------------------------------------------------------------\n";

      // Create a std::set of outlier index values.
      std::set<int> setofoutliers;
      for( std::vector<Outlier>::const_iterator it = outliers.begin(); it != outliers.end(); ++it )
      {
         setofoutliers.insert( it->index );
      }

      logfile << std::endl;
      logfile << "REMAINING OBSERVATIONS \n";
      logfile << "-------------------------------------------------------\n";
      logfile << "     #           x           y           z         uid \n";
      logfile << "-------------------------------------------------------\n";

      for( unsigned int i = 0; i < x.size(); ++i )
      {
         if( setofoutliers.find(i) == setofoutliers.end() )
         {
            logfile << std::setw(6) << i+1;
            logfile << std::fixed << std::setw(12) << std::setprecision(2) << x[i];
            logfile << std::fixed << std::setw(12) << std::setprecision(2) << y[i];
            logfile << std::fixed << std::setw(12) << std::setprecision(2) << z[i];
            logfile << std::fixed << std::setw(12) << uid[i];
            logfile << std::endl;
         }
      }
      logfile << "-------------------------------------------------------\n";
   }
   catch( BadObservations& e )
   {
      std::cerr << std::endl << std::endl;
      std::cerr << "FATAL ERROR -- bad observations" << std::endl;
      std::cerr << "Error message:            " << e.m_msg             << std::endl;
      std::cerr << "Source code filename:     " << e.m_src_filename    << std::endl;
      std::cerr << "Source code line number:  " << e.m_src_line_number << std::endl;
      std::cerr << std::endl << std::endl;

      logfile << std::endl << std::endl;
      logfile << "FATAL ERROR -- bad observations" << std::endl;
      logfile << "Error message:            " << e.m_msg             << std::endl;
      logfile << "Source code filename:     " << e.m_src_filename    << std::endl;
      logfile << "Source code line number:  " << e.m_src_line_number << std::endl;
      logfile << std::endl << std::endl;

      // Termination in the face of failure.
      logfile.close();
      return 4;
   }
   catch(...)
   {
      std::cerr << "An unknown exception was thrown! Yes, I know that this is not very informative." << std::endl;

      // Termination in the face of failure.
      logfile.close();
      throw;
   }

*/

   // Close the log file.
   logfile.close();
   std::cout << std::endl << "Log file <" << logfilename << "> was created. \n";

   // Successful termination.
   double elapsed = static_cast<double>(clock())/CLOCKS_PER_SEC;
   std::cout << std::endl << "Total elpased time: " << std::fixed << elapsed << " seconds." << std::endl;
   logfile   << std::endl << "Total elpased time: " << std::fixed << elapsed << " seconds." << std::endl;

   // Terminate exectution.
	return 0;
}

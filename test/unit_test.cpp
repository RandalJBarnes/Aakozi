//=============================================================================
// unit_test.cpp
//
// author:
//    Dr. Randal J. Barnes
//    Department of Civil, Environmental, and Geo- Engineering
//    University of Minnesota
//
// version:
//    09 June 2017
//=============================================================================
#include <iostream>

#include "..\src\matrix.h"

//-----------------------------------------------------------------------------
bool isClose( double x, double y, double tol )
{
   return( abs(x-y) < tol );
}

//-----------------------------------------------------------------------------
bool isClose( const Matrix& A, const Matrix& B, double tol )
{
   // Compare the sizes first.
   if (A.nRows() != B.nRows() || A.nCols() != B.nCols())
      return false;

   // Compare the contents.
   const double* p = A.Base();
   const double* q = B.Base();
   int n = A.nRows() * A.nCols();

   for( int k = 0; k<n; k++ )
   {
      if( abs((*p++) - (*q++)) > tol ) return false;
   }
   return true;
}

//-----------------------------------------------------------------------------
bool Check( bool test, int line, const char* file )
{
   if( !test )
   {
      std::cerr << "FAILED TEST: " << "\t LINE: " << line << "\t FILE: " << file << std::endl;
   }
   return test;
}

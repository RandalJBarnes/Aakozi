//=============================================================================
// unit_test.h
//
// author:
//    Dr. Randal J. Barnes
//    Department of Civil, Environmental, and Geo- Engineering
//    University of Minnesota
//
// version:
//    09 June 2017
//=============================================================================
#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "..\src\Matrix.h"

//=============================================================================
bool isClose( double x, double y, double tol );
bool isClose( const Matrix& A, const Matrix& B, double tol );

bool Check( bool test, int line, const char* file );

#define CHECK(X) Check( (X), __LINE__, __FILE__ )

//=============================================================================
#endif  // UNIT_TEST_H

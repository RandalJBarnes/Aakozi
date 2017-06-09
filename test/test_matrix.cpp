//=============================================================================
// test_matrix.cpp
//
// author:
//    Dr. Randal J. Barnes
//    Department of Civil, Environmental, and Geo- Engineering
//    University of Minnesota
//
// version:
//    09 June 2017
//=============================================================================
#include "test_matrix.h"

#include <utility>
#include <iomanip>
#include "unit_test.h"
#include "..\src\matrix.h"

namespace{
   const double TOLERANCE = 1e-9;
}

bool TestMatrixNullConstructor();
bool TestMatrixCopyConstructor();
bool TestMatrixSliceConstructor();
bool TestMatrixDimensionedConstructor();
bool TestMatrixConstructorWithScalarFill();
bool TestMatrixConstructorWithArrayFill();
bool TestMatrixConstructorWithStringFill();
bool TestMatrixDestructiveResize();
bool TestMatrixAssignmentOperator();
bool TestMatrixScalarAssignment();
bool TestMatrixAccess();
bool TestMatrixRowAndColumnSize();
bool TestMatrixAccessToRawStorage();
bool TestMatrixAccessToRawStorageWithOffset();
bool TestMatrixColumnSum();
bool TestMatrixRowSum();
bool TestMatrixTrace();
bool TestMatrixSum();
bool TestMatrixMaxAbs();
bool TestMatrixL1Norm();
bool TestMatrixLInfNorm();
bool TestMatrixFNorm();
bool TestMatrixTranspose();
bool TestMatrixNegative();
bool TestMatrixIdentity();
bool TestMatrixAdd_aM();
bool TestMatrixMultiply_aM();
bool TestMatrixAdd_MM();
bool TestMatrixSubtract_MM();
bool TestMatrixMultiply_MM();
bool TestMatrixMultiply_MtM();
bool TestMatrixMultiply_MMt();
bool TestMatrixMultiply_MtMt();
bool TestMatrixQuadraticForm_MtMM();
bool TestMatrixQuadraticForm_MMM();
bool TestMatrixEqual();


//=============================================================================
// Test Matrix class
//
//    Test each of the class methods.  These tests are not exhaustive, but
//    every class method is exercised and the results compared to a known
//    correct result.
//=============================================================================

//-----------------------------------------------------------------------------
// test_Matrix
//-----------------------------------------------------------------------------
std::pair<int,int> test_Matrix()
{
   int nsucc = 0;
   int nfail = 0;

   ( TestMatrixNullConstructor()                ? ++nsucc : ++nfail );
   ( TestMatrixCopyConstructor()                ? ++nsucc : ++nfail );
   ( TestMatrixSliceConstructor()               ? ++nsucc : ++nfail );
   ( TestMatrixDimensionedConstructor()         ? ++nsucc : ++nfail );
   ( TestMatrixConstructorWithScalarFill()      ? ++nsucc : ++nfail );
   ( TestMatrixConstructorWithArrayFill()       ? ++nsucc : ++nfail );
   ( TestMatrixConstructorWithStringFill()      ? ++nsucc : ++nfail );
   ( TestMatrixDestructiveResize()              ? ++nsucc : ++nfail );
   ( TestMatrixAssignmentOperator()             ? ++nsucc : ++nfail );
   ( TestMatrixScalarAssignment()               ? ++nsucc : ++nfail );
   ( TestMatrixAccess()                         ? ++nsucc : ++nfail );
   ( TestMatrixRowAndColumnSize()               ? ++nsucc : ++nfail );
   ( TestMatrixAccessToRawStorage()             ? ++nsucc : ++nfail );
   ( TestMatrixAccessToRawStorageWithOffset()   ? ++nsucc : ++nfail );
   ( TestMatrixColumnSum()                      ? ++nsucc : ++nfail );
   ( TestMatrixRowSum()                         ? ++nsucc : ++nfail );
   ( TestMatrixTrace()                          ? ++nsucc : ++nfail );
   ( TestMatrixSum()                            ? ++nsucc : ++nfail );
   ( TestMatrixMaxAbs()                         ? ++nsucc : ++nfail );
   ( TestMatrixL1Norm()                         ? ++nsucc : ++nfail );
   ( TestMatrixLInfNorm()                       ? ++nsucc : ++nfail );
   ( TestMatrixFNorm()                          ? ++nsucc : ++nfail );
   ( TestMatrixTranspose()                      ? ++nsucc : ++nfail );
   ( TestMatrixNegative()                       ? ++nsucc : ++nfail );
   ( TestMatrixIdentity()                       ? ++nsucc : ++nfail );
   ( TestMatrixAdd_aM()                         ? ++nsucc : ++nfail );
   ( TestMatrixMultiply_aM()                    ? ++nsucc : ++nfail );
   ( TestMatrixAdd_MM()                         ? ++nsucc : ++nfail );
   ( TestMatrixSubtract_MM()                    ? ++nsucc : ++nfail );
   ( TestMatrixMultiply_MM()                    ? ++nsucc : ++nfail );
   ( TestMatrixMultiply_MtM()                   ? ++nsucc : ++nfail );
   ( TestMatrixMultiply_MMt()                   ? ++nsucc : ++nfail );
   ( TestMatrixMultiply_MtMt()                  ? ++nsucc : ++nfail );
   ( TestMatrixQuadraticForm_MtMM()             ? ++nsucc : ++nfail );
   ( TestMatrixQuadraticForm_MMM()              ? ++nsucc : ++nfail );
   ( TestMatrixEqual()                          ? ++nsucc : ++nfail );

   return std::make_pair( nsucc, nfail );
}


//-----------------------------------------------------------------------------
// TestMatrixNullConstructor
//-----------------------------------------------------------------------------
bool TestMatrixNullConstructor()
{
   Matrix A;

      bool flag = true;

      flag &= CHECK( A.nRows() == 0 );
      flag &= CHECK( A.nCols() == 0 );

      return flag;
}

//-----------------------------------------------------------------------------
// TestMatrixCopyConstructor
//-----------------------------------------------------------------------------
bool TestMatrixCopyConstructor()
{
   Matrix A("1,2,3;4,5,6");
   Matrix B( A );

   return CHECK( isClose(A, B, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixSliceConstructor
//-----------------------------------------------------------------------------
bool TestMatrixSliceConstructor()
{
   Matrix A("1,2,3,4;5,6,7,8;9,10,11,12");

   std::vector<int> col_flag = { 1, 0, 1, 0 };
   std::vector<int> row_flag = { 1, 0, 1 };

   Matrix B( A, row_flag, col_flag );
   Matrix C("1,3;9,11");

   return CHECK( isClose(B, C, TOLERANCE) );
}


//-----------------------------------------------------------------------------
// TestMatrixDimensionedConstructor
//-----------------------------------------------------------------------------
bool TestMatrixDimensionedConstructor()
{
   Matrix A(2,3);
   Matrix B("0,0,0;0,0,0");

   return CHECK( isClose(A, B, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixConstructorWithScalarFill
//-----------------------------------------------------------------------------
bool TestMatrixConstructorWithScalarFill()
{
   Matrix A(2,3, 1.2);
   Matrix B("1.2,1.2,1.2;1.2,1.2,1.2");

   return CHECK( isClose(A, B, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixConstructorWithArrayFill
//-----------------------------------------------------------------------------
bool TestMatrixConstructorWithArrayFill()
{
   double A_data[] = {1.0,2.0,3.0,4.0,5.0,6.0};
   Matrix A(2,3, A_data);
   Matrix B("1,2,3;4,5,6");

   return CHECK( isClose(A, B, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixConstructorWithStringFill
//-----------------------------------------------------------------------------
bool TestMatrixConstructorWithStringFill()
{
   Matrix A("1,,;4,5,");
   Matrix B("1,0,0;4,5,0");

   return CHECK( isClose(A, B, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixDestructiveResize
//-----------------------------------------------------------------------------
bool TestMatrixDestructiveResize()
{
   Matrix A("1,2,3;4,5,6");
   A.Resize(2,2);
   Matrix B("0,0;0,0");

   return CHECK( isClose(A, B, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixAssignmentOperator
//-----------------------------------------------------------------------------
bool TestMatrixAssignmentOperator()
{
   Matrix A("1,2,3;4,5,6");
   Matrix B("0,1,1,0");
   B = A;

   return CHECK( isClose(A, B, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixScalarAssignment
//-----------------------------------------------------------------------------
bool TestMatrixScalarAssignment()
{
   Matrix A("1,2,3;4,5,6");
   A = 0.0;
   Matrix B("0,0,0;0,0,0");

   return CHECK( isClose(A, B, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixAccess
//-----------------------------------------------------------------------------
bool TestMatrixAccess()
{
   Matrix A(2,3);
   Matrix B("1,2,3;4,5,6");

   for (int i=0; i<2; ++i)
      for (int j=0; j<3; ++j)
         A(i,j) = B(i,j);

   return CHECK( isClose(A, B, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixRowAndColumnSize
//-----------------------------------------------------------------------------
bool TestMatrixRowAndColumnSize()
{
   Matrix A("1,2,3;4,5,6");

   bool flag = true;

   flag &= CHECK( A.nRows() == 2 );
   flag &= CHECK( A.nCols() == 3 );

   return flag;
}

//-----------------------------------------------------------------------------
// TestMatrixAccessToRawStorage
//-----------------------------------------------------------------------------
bool TestMatrixAccessToRawStorage()
{
   Matrix A("1,2,3;4,5,6");
   Matrix B(2,3);

   const double* pA = A.Base();
   double* pB = B.Base();

   for (int i=0; i<6; ++i)
      *pB++ = *pA++;

   return CHECK( isClose(A, B, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixAccessToRawStorageWithOffset
//-----------------------------------------------------------------------------
bool TestMatrixAccessToRawStorageWithOffset()
{
   Matrix A("1,2,3;4,5,6");
   Matrix B(2,3);

   for (int i=0; i<2; ++i)
      for (int j=0; j<3; ++j)
         *B.Base(i,j) = *A.Base(i,j);

   return CHECK( isClose(A, B, TOLERANCE) );
}


//=============================================================================
// TestMatrixAssociatedFunctions
//
//    Test each of the functions associated with the Matrix class.  These
//    tests are not exhaustive, but every function is exercised and the
//    results compared to a known correct result.
//=============================================================================

//-----------------------------------------------------------------------------
// TestMatrixColumnSum
//-----------------------------------------------------------------------------
bool TestMatrixColumnSum()
{
   Matrix A("1,2,3;4,5,6;7,8,9");
   Matrix x;
   ColumnSum( A, x );
   Matrix col_sum("12,15,18");

   return CHECK( isClose(x, col_sum, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixRowSum
//-----------------------------------------------------------------------------
bool TestMatrixRowSum()
{
   Matrix A("1,2,3;4,5,6;7,8,9");
   Matrix x;
   RowSum( A, x );
   Matrix row_sum("6;15;24");

   return CHECK( isClose(x, row_sum, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixTrace
//-----------------------------------------------------------------------------
bool TestMatrixTrace()
{
   Matrix A("1,2,3;4,5,6;7,8,9");

   return CHECK( isClose(Trace(A), 15.0, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixSum
//-----------------------------------------------------------------------------
bool TestMatrixSum()
{
   Matrix A("1,2,3;4,5,6;7,8,9");

   return CHECK( isClose(Sum(A), 45.0, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixMaxAbs
//-----------------------------------------------------------------------------
bool TestMatrixMaxAbs()
{
   Matrix A("-1,2,-3;4,-5,6;-7,8,-9");

   return CHECK( isClose(MaxAbs(A), 9.0, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixL1Norm
//-----------------------------------------------------------------------------
bool TestMatrixL1Norm()
{
   Matrix A("1,2,3;4,5,6;7,8,9");

   return CHECK( isClose(L1Norm(A), 18.0, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixLInfNorm
//-----------------------------------------------------------------------------
bool TestMatrixLInfNorm()
{
   Matrix A("1,2,3;4,5,6;7,8,9");

   return CHECK( isClose(LInfNorm(A), 24.0, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixFNorm
//-----------------------------------------------------------------------------
bool TestMatrixFNorm()
{
   Matrix A("1,2,3;4,5,6;7,8,9");

   return CHECK( isClose(FNorm(A), 16.8819430161341, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixTranspose
//-----------------------------------------------------------------------------
bool TestMatrixTranspose()
{
   Matrix A("1,2,3;4,5,6;7,8,9");
   Matrix C;
   Transpose( A, C );
   Matrix At("1,4,7; 2,5,8; 3,6,9");

   return CHECK( isClose(C, At, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixNegative
//-----------------------------------------------------------------------------
bool TestMatrixNegative()
{
   Matrix A("1,2,3;4,5,6;7,8,9");
   Matrix C;
   Negative( A, C );
   Matrix B("-1,-2,-3;-4,-5,-6;-7,-8,-9");

   return CHECK( isClose(B, C, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixIdentity
//-----------------------------------------------------------------------------
bool TestMatrixIdentity()
{
   Matrix A(3,2,1.0);
   Identity( A, 4 );
   Matrix I("1,0,0,0; 0,1,0,0; 0,0,1,0; 0,0,0,1");

   return CHECK( isClose(A, I, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixAdd_aM
//-----------------------------------------------------------------------------
bool TestMatrixAdd_aM()
{
   Matrix A("1,2,3;4,5,6");
   Matrix B;
   Add_aM(2,A,B);
   Matrix Ap2("3,4,5;6,7,8");

   return CHECK( isClose(B, Ap2, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixMultiply_aM
//-----------------------------------------------------------------------------
bool TestMatrixMultiply_aM()
{
   Matrix A("1,2,3;4,5,6");
   Matrix B;
   Multiply_aM(2,A,B);
   Matrix Ax2("2,4,6;8,10,12");

   return CHECK( isClose(B, Ax2, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixAdd_MM
//-----------------------------------------------------------------------------
bool TestMatrixAdd_MM()
{
   Matrix A("1,2,3;4,5,6");
   Matrix B("1,0,1;0,0,1");
   Matrix C;
   Add_MM(A,B,C);
   Matrix ApB("2,2,4;4,5,7");

   return CHECK( isClose(C, ApB, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixSubtract_MM
//-----------------------------------------------------------------------------
bool TestMatrixSubtract_MM()
{
   Matrix A("1,2,3;4,5,6");
   Matrix B("1,0,1;0,0,1");
   Matrix C;
   Subtract_MM(A,B,C);
   Matrix AmB("0,2,2;4,5,5");

   return CHECK( isClose(C, AmB, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixMultiply_MM
//-----------------------------------------------------------------------------
bool TestMatrixMultiply_MM()
{
   Matrix A("1,2,3;4,5,6");
   Matrix B("1,2;3,4;5,6");
   Matrix C;
   Multiply_MM(A,B,C);
   Matrix AxB("22,28; 49,64");

   return CHECK( isClose(C, AxB, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixMultiply_MtM
//-----------------------------------------------------------------------------
bool TestMatrixMultiply_MtM()
{
   Matrix A("1,4;2,5;3,6");
   Matrix B("1,2;3,4;5,6");
   Matrix C;
   Multiply_MtM(A,B,C);
   Matrix AtxB("22,28; 49,64");

   return CHECK( isClose(C, AtxB, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixMultiply_MMt
//-----------------------------------------------------------------------------
bool TestMatrixMultiply_MMt()
{
   Matrix A("1,2,3;4,5,6");
   Matrix B("1,3,5;2,4,6");
   Matrix C;
   Multiply_MMt(A,B,C);
   Matrix AxBt("22,28; 49,64");

   return CHECK( isClose(C, AxBt, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixMultiply_MtMt
//-----------------------------------------------------------------------------
bool TestMatrixMultiply_MtMt()
{
   Matrix A("1,4;2,5;3,6");
   Matrix B("1,3,5;2,4,6");
   Matrix C;
   Multiply_MtMt(A,B,C);
   Matrix AtxBt("22,28; 49,64");

   return CHECK( isClose(C, AtxBt, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixQuadraticForm_MtMM
//-----------------------------------------------------------------------------
bool TestMatrixQuadraticForm_MtMM()
{
   Matrix a("1;2;3");
   Matrix B("1,2,3;4,5,6;7,8,9");
   Matrix c("4;5;6");

   double q = QuadraticForm_MtMM(a,B,c);

   return CHECK( isClose(q, 552.0, TOLERANCE) );
}

//-----------------------------------------------------------------------------
// TestMatrixQuadraticForm_MMM
//-----------------------------------------------------------------------------
bool TestMatrixQuadraticForm_MMM()
{
   Matrix a("1,2,3");
   Matrix B("1,2,3;4,5,6;7,8,9");
   Matrix c("4;5;6");

   double q = QuadraticForm_MMM(a,B,c);

   return CHECK( isClose(q, 552.0, TOLERANCE) );
}

//=============================================================================
// Matrix comparison
//=============================================================================

//-----------------------------------------------------------------------------
// TestMatrixEqual
//-----------------------------------------------------------------------------
bool TestMatrixEqual()
{
   Matrix A("1,4;2,5;3,6");
   Matrix B("1,4;2,5;3,8");
   Matrix C("1,3,5;2,4,6");

   bool flag = true;

   flag &= CHECK( isClose(A, A, TOLERANCE) );
   flag &= CHECK( !isClose(A, B, 1.0) );
   flag &= CHECK( !isClose(A, C, TOLERANCE) );

   return flag;
}

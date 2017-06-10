//=============================================================================
// aakozi_engine.cpp
//
//    Compute the boomerang statistic for each measured location using a
//    simple linear variogram model.
//
// author:
//    Dr. Randal J. Barnes
//    Department of Civil, Environmental, and Geo- Engineering
//    University of Minnesota
//
// version:
//    09 June 2017
//=============================================================================
#include "engine.h"
#include "special_functions.h"
#include "matrix.h"
#include "linear_systems.h"

#include <numeric>
#include <math.h>
#include <iomanip>


//=============================================================================
//
//=============================================================================
std::vector<Boomerang> Engine( const std::vector<double>x, const std::vector<double>y, const std::vector<double>z, double buffer_radius )
{
   // Manifest constants.
   const int MINIMUM_COUNT = 10;
   const int N = x.size();     // number of observations.

   std::vector<Boomerang> results(N);

   // Compute the separation distance matrix for all of the observations.
   Matrix D(N, N, 0.0);
   double max_distance = 0.0;

   for( int i=0; i<N-1; ++i )
   {
      for( int j=i+1; j<N; ++j )
      {
         D(i,j) = _hypot( x[i]-x[j], y[i]-y[j] );
         D(j,i) = D(i,j);

         if( D(i,j) > max_distance )
            max_distance = D(i,j);
      }
   }

/*

   // Compute the boomerang statistic foe each observation using Ordinary
   // Kriging with a simple linear variogram.
   std::vector<double>xi(n);
   std::vector<double>zhat(n);

   // Pass through the set of observations one at a time.
   for( int n = 0; n < N; ++n )
   {
      // Gather the subset of observations used for Kriging the location of
      // observation [k]. Any observations that are within buffer radius are
      // excluded.
      int M = 0;
      for( j=1; j<N; ++j)
         if( D(k,j) > buffer_radius ) ++M;

      if( count < MINIMUM_COUNT )
      {
         results[n].zhat = nan;
         results[n].zeta = nan;
         results[n].pvalue = nan;
         results[n].count = 0;
         continue;
      }

      // Setup the Ordinary Kriging system for the location of observation [k].
      Matrix B(M,M);
      Matrix c(M,1);
      std::vector<int> index(M);

      Matrix BL, u, v, lv, w;
      Matrix ones(M,1,1.0);

      for( int i=0; k<n; ++k )
      {
         for( int i=0; i<n-1; ++i )
         {
            // Note that we subtract the distance from the maximum distance.  This
            // inversion does not change the weights, but it does make the system
            // of equations positive definite, so we can use Cholesky decomposition.
            B(i,i) = max_distance;

            for( int j=i+1; j<n-1; ++j )
            {
               B(i,j) = max_distance - D( (i<k ? i : i+1), (j<k ? j : j+1) );
               B(j,i) = B(i,j);
            }

            c(i,0) = max_distance - D( (i<k ? i : i+1), k );
         }

         // Solve the Ordinary Kringing system.
         if( !CholeskyDecomposition(B,BL) )
         {
            throw BadObservations( "Cholesky decompositon failed.", __FILE__, __LINE__ );
         }
         CholeskySolve(BL,c,u);
         CholeskySolve(BL,ones,v);

         double alpha = ( Sum(u) - 1 ) / Sum(v);

         Multiply_aM( alpha, v, lv );
         Subtract_MM( u, lv, w );

         zhat[k] = 0.0;
         for( int i=0; i<n-1; ++i )
            zhat[k] += w(i,0) * zz[ i<k ? i : i+1];

         double tau2 = max_distance - alpha;
         for( int i=0; i<n-1; ++i )
            tau2 -= w(i,0) * c(i,0);

         xi[k] = ( zz[k] - zhat[k] )/ sqrt(tau2);
      }

      // Normalize the xi to account for the unknown variogram slope.
      double sum    = 0.0;
      double sum_sq = 0.0;

      for( int i=0; i<n; ++i )
      {
         sum    += xi[i];
         sum_sq += xi[i] * xi[i];
      }
      double avg = sum/n;
      double std = sqrt( sum_sq/n - avg*avg );

      std::vector<double>zeta(n);
      for( int i=0; i<n; ++i )
         zeta[i] = xi[i]/std;

      // Find the most egregious outlier.
      int i_max = 0;
      double zeta_max = 0.0;

      for( int i=0; i<n; ++i )
      {
         if( abs(zeta[i]) > zeta_max )
         {
            i_max = i;
            zeta_max = abs(zeta[i]);
         }
      }
   }
*/

   return results;
}

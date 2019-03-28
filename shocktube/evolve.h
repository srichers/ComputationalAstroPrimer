#ifndef EVOLVE_H
#define EVOLVE_H

#include <array>

//==================//
// dConservative_dt //
//==================//
// return rate of change of conservative variables at cell centers
// given conservative fluxes at cell interfaces
// call with:
//     dcons_dt = dConservative_dt<nx>(flux, dx)
template<int nx>
array<array<double,nx>,3> dConservative_dt(const array<array<double,nx-1>,3>& flux,
					   const double dx){
  array<array<double,nx>,3> dConservative_dt;

  for(int v=0; v<3; v++)
    for(int i=1; i<nx-1; i++)
      dConservative_dt[v][i] = 0;// IMPLEMENT ME

  return dConservative_dt;
}

#endif

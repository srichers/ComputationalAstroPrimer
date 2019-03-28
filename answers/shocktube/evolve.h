#ifndef EVOLVE_H
#define EVOLVE_H

#include <array>

template<int nx>
array<array<double,nx>,3> dConservative_dt(const array<array<double,nx-1>,3>& flux,
					   const double dx){
  array<array<double,nx>,3> dConservative_dt;

  for(int v=0; v<3; v++)
    for(int i=1; i<nx-1; i++)
      dConservative_dt[v][i] = (flux[v][i-1]-flux[v][i]) / dx;

  return dConservative_dt;
}

#endif

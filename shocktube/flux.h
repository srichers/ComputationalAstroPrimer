#ifndef FLUX_H
#define FLUX_H

#include <array>

//===================//
// conservative_flux //
//===================//
// return conservative flux given primitive and conservative variables
// call with:
//     flux = conservative_flux<nx>(primitive,conservative);
template<int nx>
array<array<double,nx>,3> conservative_flux(const array<array<double,nx>,3>& primitive,
					    const array<array<double,nx>,3>& conservative){
  array<array<double,nx>,3> flux;

  // density flux
  for(int i=0; i<nx; i++)
    flux[0][i] = 0;// IMPLEMENT ME

  // momentum density flux
  for(int i=0; i<nx; i++)
    flux[1][i] = 0;// IMPLEMENT ME

  // energy density flux
  for(int i=0; i<nx; i++)
    flux[2][i] = 0;// IMPLEMENT ME

  return flux;
}

#endif

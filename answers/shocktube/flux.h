#include <array>

template<int nx>
array<array<double,nx>,3> conservative_flux(const array<array<double,nx>,3> primitive,
					    const array<array<double,nx>,3> conservative){
  array<array<double,nx>,3> flux;

  // density flux
  for(int i=0; i<nx; i++)
    flux[0][i] = conservative[1][i]; // alternatively, primitive[0]*primitive[1]

  // momentum density flux
  for(int i=0; i<nx; i++)
    flux[1][i] = primitive[0][i]*primitive[1][i]*primitive[1][i] + primitive[2][i];

  // energy density flux
  for(int i=0; i<nx; i++)
    flux[2][i] = primitive[1][i] * (conservative[2][i] + primitive[2][i]);

  return flux;
}

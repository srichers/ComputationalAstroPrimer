#include <array>

array<double,3> conservative_flux(const array<double,3> primitive, const array<double,3> conservative){
  array<double,3> flux;

  // density flux
  flux[0] = conservative[1]; // alternatively, primitive[0]*primitive[1]

  // momentum density flux
  flux[1] = primitive[0]*primitive[1]*primitive[1] + primitive[2];

  // energy density flux
  flux[2] = primitive[1] * (conservative[2] + primitive[2]);

  return flux;
}

#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <array>

//================================//
// reflecting_boundary_conditions //
//================================//
/// apply reflecting boundary conditions
// ghost zones are literally a reflection of the non-ghost zones
// call with:
//     reflecting_boundary_conditions<nx,nghost>(conservative);
template<int nx, int nghost>
void reflecting_boundary_conditions(array<array<double,nx>,3>& inout){
  // YOU NEED TO IMPLEMENT THIS
}

#endif

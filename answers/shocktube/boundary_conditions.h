#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <array>

// apply reflecting boundary conditions
// ghost zones are literally a reflection of the non-ghost zones
// call with:
//     reflecting_boundary_conditions<nx,nghost>(conservative);
template<int nx, int nghost>
void reflecting_boundary_conditions(array<array<double,nx>,3>& inout){
  for(int v=0; v<3; v++){
    for(int i=0; i<nghost; i++){
      inout[v][i            ] = inout[v][2*nghost-1-i];
      inout[v][nx-nghost + i] = inout[v][nx-1-nghost-i];
    }
  }
}

#endif

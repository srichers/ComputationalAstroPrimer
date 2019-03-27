#include <array>

template<typename T, int nx, int nghost>
void reflecting_boundary_conditions(array<T,nx>& inout){
  assert(nx > 2*nghost);

  // set reflecting boundary conditions
  for(int i=0; i<nghost; i++){
    inout[i] = inout[2*nghost-1-i];
    inout[nx-nghost + i] = inout[nx-1-nghost-i];
  }
}
